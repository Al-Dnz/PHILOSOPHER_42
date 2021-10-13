/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adenhez <adenhez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/02 21:06:58 by adenhez           #+#    #+#             */
/*   Updated: 2021/10/13 21:26:48 by adenhez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
void	log_line(t_philo *philo, char *message)
{
	pthread_mutex_lock(philo->message_locker);
	display_timestamp(*philo);
	write(1, " ", 1);
	write(1, "philo#", 6);
	ft_putnbr_fd(philo->id, 1);
	write(1, " ", 1);
	ft_putstr_fd(message, 1);
	write(1, "\n", 1);
	pthread_mutex_unlock(philo->message_locker);
}

void	*philo_routine(void *arg)
{
	t_philo *philo;

	philo = (t_philo*)arg;
	if (philo->id % 2 == 0)
		usleep(philo->t_eat * 0.9 + 1);
	while (philo->meal_limit == -1 || philo->meal_count < philo->meal_limit)
	{
		pthread_mutex_lock(philo->prev_fork);
		log_line(philo, "has taken a fork");
		pthread_mutex_lock(&philo->fork);
		log_line(philo, "has taken a fork");
		log_line(philo, "is eating");
		usleep(philo->t_eat);
		pthread_mutex_unlock(&philo->fork);
		pthread_mutex_unlock(philo->prev_fork);
		philo->meal_count++;
		log_line(philo, "is sleeping");
		usleep(philo->t_sleep);
		log_line(philo, "is thinking");
	}
	return (NULL);
}

void	*meal_check(void *arg)
{
	t_philo *philo;
	int i;
	int n;

	i = 0;
	philo = (t_philo*)arg;
	n = philo[0].n_philo;
	while (i < n)
	{
		pthread_mutex_lock(philo[0].meal_checker);
		i++;
	}
	return (NULL);
}



void	philo_array_generator(t_data *data, t_philo *philo)
{
	int	i;
	struct timeval	init_time;
	
	gettimeofday(&init_time, NULL);
	i = 0;
	while (i < data->n_philo)
	{
		philo[i].message_locker = &data->message_locker;
		philo[i].meal_checker = &data->meal_checker;
		philo[i].end_of_simulation = &data->end_of_simulation;
		pthread_mutex_init(&philo[i].fork, NULL);
		if (i > 0)
			philo[i].prev_fork = &philo[i - 1].fork;
		else
			philo[i].prev_fork = NULL;
		philo[i].n_philo = data->n_philo;
		philo[i].id = i + 1;
		philo[i].t_die = data->t_to_die;
		philo[i].t_eat = data->t_to_eat;
		philo[i].t_sleep = data->t_to_sleep;
		philo[i].meal_limit = data->meal_limit;
		philo[i].meal_count = 0;
		philo[i].init_time = init_time.tv_sec;
		i++;
	}
	philo[0].prev_fork = &philo[data->n_philo - 1].fork;
}

void	philosophers(t_data *data, t_philo *philo, pthread_t *thread_arr)
{
	int		i;
	pthread_t meal_thread;
	
	philo_array_generator(data, philo);
	i = -1;
	while (++i < data->n_philo)
		pthread_create(&thread_arr[i], NULL, philo_routine, &(philo[i]));
	i = -1;
	while (++i < data->n_philo)
		pthread_join(thread_arr[i], NULL);
	
	if (data->meal_limit > -1)
	{
		pthread_create(&meal_thread, NULL, meal_check, &philo);
		pthread_join(meal_thread, NULL);
	}

	pthread_mutex_destroy(&data->message_locker);
	pthread_mutex_destroy(&data->meal_checker);
	pthread_mutex_destroy(&data->end_of_simulation);
}

void	store_data(int argc, char **argv, t_data *data)
{
	pthread_mutex_init(&data->message_locker, NULL);
	pthread_mutex_init(&data->meal_checker, NULL);
	pthread_mutex_init(&data->end_of_simulation, NULL);
	data->n_philo = ft_atoi(argv[1]);
	data->t_to_die = ft_atoi(argv[2]);
	data->t_to_eat = ft_atoi(argv[3]);
	data->t_to_sleep = ft_atoi(argv[4]);
	if (argc == 6 && ft_atoi(argv[5]) > 0)
		data->meal_limit = ft_atoi(argv[5]);
	else
		data->meal_limit = -1;
}	

int	dipslay_usage(char *message, int fd)
{
	ft_putstr_fd(message, 1);
	ft_putstr_fd("Usage:\n", fd);
	ft_putstr_fd("      ./philo [n_of_philosophers] [time_to_die]", fd);
	ft_putstr_fd(" [time_to_eat] [time_to_sleep] [time_they_must_eat]\n", 1);
	return (1);
}

int	arg_error(int argc, char **argv)
{
	int	i;
	int	j;

	if (argc < 5 || argc > 6)
		return (dipslay_usage("Error\nWrong arguments number\n", 2));
	i = 0;
	while (++i < argc)
	{
		if (i < 5 && ft_atoi(argv[i]) < 1)
			return 
				(dipslay_usage
				("Error\nEvery arg must be an integer higher than zero\n", 2));
		j = -1;
		while (argv[i][++j])
		{
			if (!ft_isdigit(argv[i][j]))
				return (dipslay_usage("Error\nEvery arg must be numeric\n", 2));
		}
	}
	return (0);
}



int	main(int argc, char **argv)
{
	t_data			data;
	t_philo			*philo;
	pthread_t		*thread_arr;
	
	thread_arr = NULL;
	philo = NULL;
	if (arg_error(argc, argv))
		return (EXIT_FAILURE);
	store_data(argc, argv, &data);
	philo = malloc(sizeof(t_philo) * data.n_philo);
	if (philo == NULL)
		ft_exit("Error in philo array initialisation\n", EXIT_FAILURE, 2);
	thread_arr = malloc(sizeof(pthread_t) * data.n_philo);
	if (thread_arr == NULL)
	{
		free(philo);
		ft_exit("Error in thread initialisation\n", EXIT_FAILURE, 2);
	}
	philosophers(&data, philo, thread_arr);
	free(thread_arr);
	free(philo);
	return (EXIT_SUCCESS);
}
