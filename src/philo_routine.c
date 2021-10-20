/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adenhez <adenhez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 12:33:31 by adenhez           #+#    #+#             */
/*   Updated: 2021/10/20 22:45:07 by adenhez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	routine_process(t_philo *philo)
{
	pthread_mutex_lock(philo->prev_fork);
	log_line(philo, "has taken a L fork");
	pthread_mutex_lock(&philo->fork);
	log_line(philo, "has taken a R fork");
	log_line(philo, "is eating");
	philo->meal_count++;
	usleep(philo->t_eat * 1000);
	philo->last_meal = get_time_now();
	pthread_mutex_unlock(&philo->fork);
	pthread_mutex_unlock(philo->prev_fork);
	if (philo->alive == false)
		return ;
	log_line(philo, "is sleeping");
	usleep(philo->t_sleep * 1000);
	if (philo->alive == false)
		return ;
	log_line(philo, "is thinking");
}

void	*philo_routine(void *arg)
{
	t_philo		*philo;
	pthread_t	death_thread;

	philo = (t_philo *)arg;
	pthread_create(&death_thread, NULL, mower_check, philo);
	if (philo->id % 2 == 0)
		usleep(philo->t_eat * 1000);
	while (philo->n_philo > 1 && philo->alive && (philo->meal_limit == -1
			|| philo->meal_count < philo->meal_limit))
		routine_process(philo);
	pthread_mutex_unlock(philo->meal_checker);
	return (NULL);
}
