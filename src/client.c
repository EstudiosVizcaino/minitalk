/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvizcain <cvizcain@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 01:29:20 by cvizcain          #+#    #+#             */
/*   Updated: 2025/07/13 01:51:17 by cvizcain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minitalk.h"

static int	ft_atoi(const char *str)
{
	int	sign;
	int	nbr;

	sign = 1;
	nbr = 0;
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '-')
	{
		sign = -1;
		str++;
	}
	else if (*str == '+')
		str++;
	while (*str >= '0' && *str <= '9')
	{
		nbr = nbr * 10 + *str - 48;
		str++;
	}
	return (nbr * sign);
}

int	ft_send_byte(unsigned char byte, int pid)
{
	int	error;
	int	bit_count;

	error = 0;
	bit_count = 0;
	while (!error && bit_count < 8)
	{
		if ((byte & 0b10000000) == 0b10000000)
			error = kill(pid, SIGUSR2);
		else
			error = kill(pid, SIGUSR1);
		byte = byte << 1;
		bit_count++;
		usleep(500);
	}
	return (error);
}

int	main(int argc, char **argv)
{
	if (argc != 3)
		return (0);
	while (*argv[2])
	{
		if (ft_send_byte(*argv[2], ft_atoi(argv[1])) == -1)
			(write (2, "Error sending signal.\n", 22), exit (-1));
		argv[2]++;
		usleep(500);
	}
	if (ft_send_byte('\n', ft_atoi(argv[1])) == -1)
		(exit (-1));
}

