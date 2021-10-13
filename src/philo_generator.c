/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_generator.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adenhez <adenhez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/02 21:06:36 by adenhez           #+#    #+#             */
/*   Updated: 2021/10/13 19:55:11 by adenhez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*routine_1(void *arg)
{
	//(void)arg;
	t_philo *philo;
	philo = (t_philo*)arg;
	while (1)
	{
		usleep(DELAY);
		display_timestamp(*philo);
		ft_putstr_fd("\n", 1);
	}	
	//pthread_exit(NULL);
}

void	*routine_2(void *arg)
{
	(void)arg;
	while (1)
	{
		usleep(DELAY);
		//ft_putstr_fd("OOOOOOOO\n", 1);
	}
	//pthread_exit(NULL);
}

