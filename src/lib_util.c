/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib_util.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adenhez <adenhez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/02 21:06:44 by adenhez           #+#    #+#             */
/*   Updated: 2021/10/20 12:26:07 by adenhez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_isdigit(int c)
{
	if (c >= 48 && c <= 57)
		return (1);
	else
		return (0);
}

long	ft_atoi(const char *str)
{
	long int	res;
	int			i;
	long int	sign;

	res = 0;
	i = 0;
	sign = 1;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while (ft_isdigit(str[i]) && str[i])
	{
		res = res * 10 + str[i] - '0';
		if (res > 2147483647 && ft_isdigit(str[i + 1]) && sign > 0)
			return (-1);
		else if (res > 2147483648 && ft_isdigit(str[i + 1]) && sign < 0)
			return (0);
		i++;
	}
	return (res * sign);
}

void	ft_putnbr_fd(long long n, int fd)
{
	char	c;

	if (n == -2147483648)
	{
		write(fd, "-2147483648", 11);
		return ;
	}
	if (n < 0)
	{
		write(fd, "-", 1);
		n *= -1;
	}
	if (n >= 10)
		ft_putnbr_fd(n / 10, fd);
	c = n % 10 + '0';
	write(fd, &c, 1);
}

void	ft_putstr_fd(char *str, int fd)
{
	int	i;

	i = 0;
	while (str[i])
		write (fd, &str[i++], 1);
}

void	ft_exit(char *message, int error, int fd)
{
	ft_putstr_fd(message, fd);
	exit(error);
}
