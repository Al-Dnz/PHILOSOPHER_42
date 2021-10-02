/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adenhez <adenhez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/02 21:06:58 by adenhez           #+#    #+#             */
/*   Updated: 2021/10/02 21:09:00 by adenhez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	dipslay_usage(char *message, int fd)
{
	ft_putstr_fd(message, 1);
	ft_putstr_fd("Usage => ", fd);
	ft_putstr_fd("./philo [n_of_philosophers][time_to_die][time_to_eat]", fd);
	ft_putstr_fd("[time_to_sleep][time_they_must_eat]\n", 1);
	return (1);
}

int	arg_error(int argc, char **argv)
{
	int	i;
	int	j;

	if (argc != 6)
		return (dipslay_usage("Error\nWrong arguments number\n", 1));
	i = 0;
	while (++i < argc)
	{
		if (ft_atoi(argv[i]) < 1)
			(dipslay_usage("Error\nEvery arg must be higher than zero\n", 1));
		j = -1;
		while (argv[i][++j])
		{
			if (!ft_isdigit(argv[i][j]))
				return (dipslay_usage("Error\nEvery arg must be numeric\n", 1));
		}
	}
	return (0);
}

void	store_philo_data(char **argv, t_philo_data *data)
{
	data->n_philo = ft_atoi(argv[1]);
	data->t_to_die = ft_atoi(argv[2]);
	data->t_to_eat = ft_atoi(argv[3]);
	data->t_to_sleep = ft_atoi(argv[4]);
	data->t_must_eat = ft_atoi(argv[5]);
}

int	main(int argc, char **argv)
{
	t_philo_data	data;
	pthread_t		*thread_arr;
	int				i;
	// static void *(*f[2])(void*) = {&routine_1, &routine_2};
	
	thread_arr = NULL;
	if (arg_error(argc, argv))
		return (EXIT_FAILURE);
	store_philo_data(argv, &data);
	thread_arr = malloc(sizeof(pthread_t) * (data.n_philo + 1));
	if (thread_arr == NULL)
		ft_exit("Error in thread initialisation\n", EXIT_FAILURE, 2);
	i = -1;
	while (++i < data.n_philo)
		pthread_create(&thread_arr[i], NULL, routine_1, NULL);
	thread_arr[i] = NULL;
	i = -1;
	while (++i < data.n_philo)
		pthread_join(thread_arr[i], NULL);
	free(thread_arr);
	return (EXIT_SUCCESS);
}
