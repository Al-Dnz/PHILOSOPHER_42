/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adenhez <adenhez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 12:23:16 by adenhez           #+#    #+#             */
/*   Updated: 2021/10/23 13:06:46 by adenhez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	display_timestamp(long long init_time)
{
	int	time;

	time = get_time_now() - init_time;
	zero_norm(time, TIMESTAMP_NORM);
	ft_putnbr_fd(time, 1);
}

void	zero_norm(long long n, int limit)
{
	int	dimension;
	int	n_bis;

	dimension = 0;
	n_bis = n;
	while (n_bis > 0)
	{
		dimension++;
		n_bis /= 10;
	}
	if (dimension > limit)
		return ;
	if (n == 0)
		dimension = 1;
	while (limit-- - dimension)
		write(1, "0", 1);
}

long long	get_time_now(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + time.tv_usec / 1000);
}

void	micro_sleep(long t)
{
	long long	init_time;

	if (t < 10)
	{
		usleep(t * 1000);
		return ;
	}
	init_time = get_time_now();
	while (get_time_now() < init_time + t)
		usleep(t);
}
