/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adenhez <adenhez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 12:33:31 by adenhez           #+#    #+#             */
/*   Updated: 2021/10/23 00:13:17 by adenhez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	routine_process(t_philo *philo)
{
	while (*philo->death_signal == 0 && philo->n_philo > 1
			&& (philo->meal_limit == -1
			|| philo->meal_count < philo->meal_limit))
	{
		if (*philo->death_signal)
			return ;
		pthread_mutex_lock(philo->prev_fork);
		log_line(philo, "has taken a L fork");
		if (*philo->death_signal)
			return ;
		pthread_mutex_lock(&philo->fork);
		log_line(philo, "has taken a R fork");
		log_line(philo, "is eating");
		philo->is_eating = true;
		philo->meal_count++;
		usleep(philo->t_eat * 1000);
		philo->last_meal = get_time_now();
		pthread_mutex_unlock(philo->prev_fork);
		pthread_mutex_unlock(&philo->fork);
		philo->is_eating = false;
		if (*philo->death_signal)
			return ;
		log_line(philo, "is sleeping");
		usleep(philo->t_sleep * 1000);
		if (*philo->death_signal)
			return ;
		log_line(philo, "is thinking");
	}
	philo->satiated = true;
}

void	*philo_routine(void *arg)
{
	t_philo		*philo;

	philo = (t_philo *)arg;
	if (philo->n_philo == 1)
		return (NULL);
	if (philo->id % 2 == 0)
		usleep(philo->t_eat * 1000);
	routine_process(philo);
	pthread_mutex_unlock(philo->meal_checker);
	return (NULL);
}
