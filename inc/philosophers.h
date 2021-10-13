#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <stdbool.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct	s_data
{
	pthread_mutex_t message_locker;
	pthread_mutex_t meal_checker;
	pthread_mutex_t end_of_simulation;
	int n_philo;
	int	t_to_die;
	int	t_to_eat;
	int	t_to_sleep;
	int	meal_limit;
}				t_data;

typedef struct s_philo
{
	pthread_mutex_t fork;
	pthread_mutex_t *prev_fork;
	pthread_mutex_t *message_locker;
	pthread_mutex_t *meal_checker;
	pthread_mutex_t *end_of_simulation;
	int	n_philo;
	int init_time;
	int	t_die;
	int	t_eat;
	int	t_sleep;
	int	meal_limit;
	int	meal_count;
	int	id;
}				t_philo;


#define DELAY 1000000

//philo_generator.c
void		*routine_1(void *arg);
void		*routine_2(void *arg);

//lib_util_1.c
void		ft_putstr_fd(char *str, int fd);
void		ft_exit(char *message, int error, int fd);

//lib_util_2.c
long		ft_atoi(const char *str);
int			ft_isdigit(int c);
void		ft_putnbr_fd(int n, int fd);

//time_handler.c
void	display_timestamp(t_philo philo);

#endif