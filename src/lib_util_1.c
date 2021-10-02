/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib_util_1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adenhez <adenhez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/02 21:06:49 by adenhez           #+#    #+#             */
/*   Updated: 2021/10/02 21:09:26 by adenhez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_putstr_fd(char *str, int fd)
{
	int	i;

	i = 0;
	while (str[i])
		write (fd, &str[i++], 1);
}

void	ft_exit(char *message, int error, int fd)
{
	/*
	** some code
	*/
	ft_putstr_fd(message, fd);
	exit(error);
}
