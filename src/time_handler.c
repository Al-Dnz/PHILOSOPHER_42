#include "philosophers.h"

void	display_timestamp(t_philo philo)
{
	int				time_bis;
	int				time;
	int				dimension;
	int				display_len;
	struct timeval	now;

	gettimeofday(&now, NULL);
	time_bis = now.tv_sec - philo.init_time;
	dimension = 0;
	time = time_bis;
	while (time_bis > 0)
	{
		dimension++;
		time_bis /= 10;
	}
	display_len = 6;
	while (--display_len - dimension)
	 	write(1, "0", 1);
	ft_putnbr_fd(time, 1);
}