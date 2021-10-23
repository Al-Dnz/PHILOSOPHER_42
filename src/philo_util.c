/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adenhez <adenhez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 12:11:24 by adenhez           #+#    #+#             */
/*   Updated: 2021/10/23 12:39:20 by adenhez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	log_line(t_philo *philo, char *message)
{
	
	pthread_mutex_lock(philo->message_locker);
	if (*philo->death_signal == 1 || *philo->meal_signal == 1)
	{
		pthread_mutex_unlock(philo->message_locker);
		return ;
	}
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
	while (*philo->death_signal == 0 && *philo->meal_signal == 0
		&& philo->satiated == false)
	{
		if (philo->is_eating == false && ((philo->last_meal != -1
					&& (get_time_now() - philo->last_meal) > philo->t_die)
				|| (philo->n_philo == 1
					&& get_time_now() - philo->init_time > philo->t_die)))
		{
			log_line(philo, "has died");
			*philo->death_signal = 1;
			break ;
		}
	}
	if (philo->n_philo > 1)
		pthread_mutex_unlock(philo->prev_fork);
	pthread_mutex_unlock(&philo->fork);
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
	if (*philo[0].death_signal == 1 || n == 1)
		return (NULL);
	while (i <= n && philo[0].meal_limit > 0)
	{
		if (*philo[0].death_signal == 1)
			return (NULL);
		pthread_mutex_lock(philo[0].meal_checker);
		i++;
	}
	*philo[0].meal_signal = 1;
	if (*philo->death_signal == 0)
	{
		display_timestamp(philo[0].init_time);
		ft_putstr_fd(" All meals have been taken\n", 1);
	}
	return (NULL);
}

void	set_philo(t_philo *philo, t_data *data, long long init_time, int i)
{
	philo->message_locker = &data->message_locker;
	philo->meal_checker = &data->meal_checker;
	philo->end_of_simulation = &data->end_of_simulation;
	philo->n_philo = data->n_philo;
	philo->id = i + 1;
	philo->t_die = data->t_before_die;
	philo->t_eat = data->t_of_meal;
	philo->t_sleep = data->t_of_sleep;
	philo->meal_limit = data->meal_limit;
	philo->meal_count = 0;
	philo->init_time = init_time;
	philo->last_meal = -1;
	philo->death_signal = &data->death_signal;
	philo->meal_signal = &data->meal_signal;
	philo->satiated = false;
	philo->is_eating = false;
}

void	philo_array_generator(t_data *data, t_philo *philo)
{
	int			i;
	long long	init_time;

	init_time = get_time_now();
	i = -1;
	while (++i < data->n_philo)
	{
		pthread_mutex_init(&philo[i].fork, NULL);
		if (i > 0)
			philo[i].prev_fork = &philo[i - 1].fork;
		else
			philo[i].prev_fork = NULL;
		set_philo(&philo[i], data, init_time, i);
	}
	if (data->n_philo > 1)
		philo[0].prev_fork = &philo[data->n_philo - 1].fork;
}
