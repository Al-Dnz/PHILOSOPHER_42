/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_generator.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adenhez <adenhez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/02 21:06:36 by adenhez           #+#    #+#             */
/*   Updated: 2021/10/02 21:06:38 by adenhez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#define DELAY 1000000

void	*routine_1(void *arg)
{
	(void)arg;
	while (1)
	{
		usleep(DELAY);
		ft_putstr_fd("XXXXXXXXX\n", 1);
	}	
	pthread_exit(NULL);
}

void	*routine_2(void *arg)
{
	(void)arg;
	while (1)
	{
		usleep(DELAY);
		ft_putstr_fd("OOOOOOOO\n", 1);
	}
	pthread_exit(NULL);
}

pthread_t	philo_generator(void *routine(void *arg))
{
	pthread_t	thread;
	int			process;

	process = pthread_create(&thread, NULL, routine, NULL);
	if (process != 0)
		ft_exit("Error in thread creation\n", EXIT_FAILURE, 2);
	return (thread);
}
