/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adenhez <adenhez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/02 21:06:58 by adenhez           #+#    #+#             */
/*   Updated: 2021/10/11 17:03:29 by adenhez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

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

void	store_data(int argc, char **argv, t_data *data)
{
	data->n_philo = ft_atoi(argv[1]);
	data->t_to_die = ft_atoi(argv[2]);
	data->t_to_eat = ft_atoi(argv[3]);
	data->t_to_sleep = ft_atoi(argv[4]);
	if (argc == 6 && ft_atoi(argv[5]) > 0)
		data->meal_limit = ft_atoi(argv[5]);
	else
		data->meal_limit = -1;
}		
void	philosophers(t_data *data, t_philo *philo, pthread_t *thread_arr)
{
	int				i;
	struct timeval	time;
	
	i = -1;
	while (++i < data->n_philo)
		pthread_create(&thread_arr[i], NULL, routine_2, NULL);
		//pthread_create(&thread_arr[i], NULL, routine_1, philo);

	thread_arr[i] = NULL;
	gettimeofday(&time, NULL);
	philo->init_time = time.tv_sec;
	i = -1;
	while(1)
	{
		usleep(DELAY);
		display_timestamp(philo);
		write(1, "\n", 1);
	}
	
	while (++i < data->n_philo)
		pthread_join(thread_arr[i], NULL);
}

void	philo_array_generator(t_data data, t_philo *philo)
{
	int	i;
	struct timeval	init_time;

	i = 0;
	gettimeofday(&init_time, NULL);
	while (i < data.n_philo)
	{
		philo[i].id = i + 1;
		philo[i].t_die = data.t_to_die;
		philo[i].t_eat = data.t_to_eat;
		philo[i].t_sleep = data.t_to_sleep;
		philo[i].init_time = init_time.tv_sec;
		i++;
	}
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
	philo = malloc(sizeof(t_philo) * (data.n_philo));
	if (philo == NULL)
		ft_exit("Error in philo array initialisation\n", EXIT_FAILURE, 2);
	thread_arr = malloc(sizeof(pthread_t) * (data.n_philo + 1));
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
