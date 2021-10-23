/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adenhez <adenhez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 12:58:44 by adenhez           #+#    #+#             */
/*   Updated: 2021/10/23 11:41:04 by adenhez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <stdbool.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_data
{
	pthread_mutex_t	message_locker;
	pthread_mutex_t	meal_checker;
	pthread_mutex_t	end_of_simulation;
	int				n_philo;
	int				t_before_die;
	int				t_of_meal;
	int				t_of_sleep;
	int				meal_limit;
	int				death_signal;
	int				meal_signal;
}				t_data;

typedef struct s_philo
{
	pthread_t		death_thread;
	pthread_mutex_t	fork;
	pthread_mutex_t	*prev_fork;
	pthread_mutex_t	*message_locker;
	pthread_mutex_t	*meal_checker;
	pthread_mutex_t	*end_of_simulation;
	int				*death_signal;
	int				*meal_signal;
	int				n_philo;
	long long		init_time;
	int				t_die;
	int				t_eat;
	int				t_sleep;
	int				meal_limit;
	int				meal_count;
	long long		last_meal;
	int				id;
	bool			satiated;
	bool			is_eating;
}				t_philo;

# define DELAY 1000000
# define END_DELAY 100
# define TIMESTAMP_NORM 6

void		log_line(t_philo *philo, char *message);
void		*mower_check(void *arg);
void		*meal_check(void *arg);
void		*philo_routine(void *arg);
void		philo_array_generator(t_data *data, t_philo *philo);

void		ft_putstr_fd(char *str, int fd);
void		ft_exit(char *message, int error, int fd);
long		ft_atoi(const char *str);
int			ft_isdigit(int c);
void		ft_putnbr_fd(long long n, int fd);

void		display_timestamp(long long init_time);
void		zero_norm(long long n, int limit);
long long	get_time_now(void);

void		*checker(void *arg);
void		philosophers(t_data *data, t_philo *philo, pthread_t *thread_arr);
void		thread_detacher(pthread_t *thread_arr, t_data *data,
				t_philo *philo);
void		thread_joiner(pthread_t *thread_arr, t_data *data, t_philo *philo);
void		mutex_destroyer(t_data *data, t_philo *philo);

#endif