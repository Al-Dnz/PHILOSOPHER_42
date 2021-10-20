/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adenhez <adenhez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/02 21:06:58 by adenhez           #+#    #+#             */
/*   Updated: 2021/10/20 22:33:20 by adenhez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	philosophers(t_data *data, t_philo *philo, pthread_t *thread_arr)
{
	int			i;
	pthread_t	meal_thread;

	philo_array_generator(data, philo);
	i = -1;
	if (data->meal_limit > -1 && data->n_philo > 1)
		pthread_create(&meal_thread, NULL, meal_check, philo);
	while (++i < data->n_philo)
		pthread_create(&thread_arr[i], NULL, philo_routine, &(philo[i]));
	pthread_mutex_lock(&data->end_of_simulation);
	usleep(END_DELAY);
	i = -1;
	while (++i < data->n_philo)
	{
		pthread_detach(thread_arr[i]);
		pthread_detach(philo[i].death_thread);
		pthread_mutex_destroy(&philo[i].fork);
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
	pthread_mutex_lock(&data->end_of_simulation);
	data->n_philo = ft_atoi(argv[1]);
	data->t_before_die = ft_atoi(argv[2]);
	data->t_of_meal = ft_atoi(argv[3]);
	data->t_of_sleep = ft_atoi(argv[4]);
	if (argc == 6 && ft_atoi(argv[5]) >= 0)
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
		if ((i < 5 && ft_atoi(argv[i]) < 1) || (i == 5 && ft_atoi(argv[i]) < 0))
			return (dipslay_usage
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
