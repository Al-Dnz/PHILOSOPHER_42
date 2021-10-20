/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adenhez <adenhez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 12:11:24 by adenhez           #+#    #+#             */
/*   Updated: 2021/10/20 12:49:11 by adenhez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	log_line(t_philo *philo, char *message)
{
	pthread_mutex_lock(philo->message_locker);
	display_timestamp(philo->init_time);
	write(1, " ", 1);
	if (philo != NULL)
	{
		write(1, "philosopher#", 12);
		zero_norm(philo->id, 3);
		ft_putnbr_fd(philo->id, 1);
		write(1, " ", 1);
	}
	ft_putstr_fd(message, 1);
	write(1, "\n", 1);
	pthread_mutex_unlock(philo->message_locker);
}

void	*mower_check(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		if ((philo->last_meal != 0
				&& ((get_time_now() - philo->last_meal) > philo->t_die))
			|| (get_time_now() - philo->init_time > philo->t_die
				&& philo->n_philo == 1))
		{
			log_line(philo, "has died");
			philo->alive = false;
			pthread_mutex_unlock(philo->end_of_simulation);
			return (NULL);
		}
	}
	return (NULL);
}

void	*meal_check(void *arg)
{
	t_philo	*philo;
	int		i;
	int		n;

	i = 0;
	philo = (t_philo *)arg;
	n = philo[0].n_philo;
	while (i < n && philo[0].meal_limit > 0)
	{
		pthread_mutex_lock(philo[0].meal_checker);
		i++;
	}
	pthread_mutex_lock(philo[0].message_locker);
	display_timestamp(philo[0].init_time);
	ft_putstr_fd(" All meals have been taken", 1);
	pthread_mutex_unlock(philo[0].message_locker);
	pthread_mutex_unlock(philo[0].end_of_simulation);
	return (NULL);
}

void	set_philo(t_philo *philo, t_data *data, long long init_time, int i)
{
	philo->message_locker = &data->message_locker;
	philo->meal_checker = &data->meal_checker;
	philo->end_of_simulation = &data->end_of_simulation;
	pthread_mutex_init(&philo->fork, NULL);
	if (i > 0)
		philo->prev_fork = &philo[i - 1].fork;
	else
		philo->prev_fork = NULL;
	philo->n_philo = data->n_philo;
	philo->id = i + 1;
	philo->t_die = data->t_before_die;
	philo->t_eat = data->t_of_meal;
	philo->t_sleep = data->t_of_sleep;
	philo->meal_limit = data->meal_limit;
	philo->meal_count = 0;
	philo->init_time = init_time;
	philo->last_meal = 0;
	philo->alive = true;
}

void	philo_array_generator(t_data *data, t_philo *philo)
{
	int			i;
	long long	init_time;

	init_time = get_time_now();
	i = -1;
	while (++i < data->n_philo)
		set_philo(&philo[i], data, init_time, i);
	if (data->n_philo > 1)
		philo[0].prev_fork = &philo[data->n_philo - 1].fork;
}
