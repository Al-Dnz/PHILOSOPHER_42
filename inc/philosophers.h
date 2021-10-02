#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <stdbool.h>
# include <pthread.h>

typedef struct	s_philo_data
{
	int n_philo;
	int	t_to_die;
	int	t_to_eat;
	int	t_to_sleep;
	int	t_must_eat;
}				t_philo_data;

//philo_generator.c
void		*routine_1(void *arg);
void		*routine_2(void *arg);
pthread_t	philo_generator(void *(routine)(void *arg));

//lib_util_1.c
void		ft_putstr_fd(char *str, int fd);
void		ft_exit(char *message, int error, int fd);

//lib_util_2.c
long		ft_atoi(const char *str);
int			ft_isdigit(int c);
void		ft_putnbr_fd(int n, int fd);

#endif