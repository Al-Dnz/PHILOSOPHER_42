/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_util.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adenhez <adenhez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/23 01:01:10 by adenhez           #+#    #+#             */
/*   Updated: 2021/10/23 12:26:33 by adenhez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*checker(void *arg)
{
	t_data	*data;

	data = (t_data *)arg;
	while (data->meal_signal == 0 && data->death_signal == 0)
		continue ;
	pthread_mutex_unlock(&data->end_of_simulation);
	return (NULL);
}

void	philosophers(t_data *data, t_philo *philo, pthread_t *thread_arr)
{
	int			i;
	pthread_t	meal_thread;
	pthread_t	main_checker;

	philo_array_generator(data, philo);
	pthread_create(&main_checker, NULL, checker, data);
	if (data->meal_limit > -1 && data->n_philo > 1)
		pthread_create(&meal_thread, NULL, meal_check, philo);
	i = -1;
	while (++i < data->n_philo)
	{
		pthread_create(&thread_arr[i], NULL, philo_routine, &(philo[i]));
		pthread_create(&philo[i].death_thread, NULL, mower_check, &philo[i]);
	}
	thread_joiner(thread_arr, data, philo);
	pthread_join(main_checker, NULL);
	if (data->meal_limit > -1 && data->n_philo > 1)
		pthread_join(meal_thread, NULL);
	pthread_mutex_lock(&data->end_of_simulation);
	usleep(END_DELAY);
	mutex_destroyer(data, philo);
}

void	thread_joiner(pthread_t *thread_arr, t_data *data, t_philo *philo)
{
	int	i;

	i = -1;
	while (++i < data->n_philo)
	{
		pthread_join(thread_arr[i], NULL);
		pthread_join(philo[i].death_thread, NULL);
	}
}

void	thread_detacher(pthread_t *thread_arr, t_data *data, t_philo *philo)
{
	int	i;

	i = -1;
	while (++i < data->n_philo)
	{
		pthread_detach(thread_arr[i]);
		pthread_detach(philo[i].death_thread);
	}
}

void	mutex_destroyer(t_data *data, t_philo *philo)
{
	int	i;

	i = -1;
	pthread_mutex_destroy(&data->message_locker);
	pthread_mutex_destroy(&data->meal_checker);
	pthread_mutex_destroy(&data->end_of_simulation);
	while (++i < data->n_philo)
		pthread_mutex_destroy(&philo[i].fork);
}
