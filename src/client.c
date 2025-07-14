/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvizcain <cvizcain@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 01:29:20 by cvizcain          #+#    #+#             */
/*   Updated: 2025/07/14 19:10:38 by cvizcain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minitalk.h"

static volatile sig_atomic_t	g_ack_received = 1;

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

void	ack_handler(int sig)
{
	(void)sig;
	g_ack_received = 1;
}

void	ft_send_byte(unsigned char byte, int pid)
{
	int	i;

	i = 8;
	while (i--)
	{
		while (!g_ack_received)
			usleep(50);
		g_ack_received = 0;
		if ((byte >> i) & 1)
			kill(pid, SIGUSR2);
		else
			kill(pid, SIGUSR1);
	}
}

int	main(int argc, char **argv)
{
	int		pid;
	char	*message;

	if (argc != 3)
		return (ft_printf("Usage: ./client [PID] [MESSAGE]\n"), 1);
	signal(SIGUSR1, ack_handler);
	pid = ft_atoi(argv[1]);
	message = argv[2];
	while (*message)
	{
		ft_send_byte(*message, pid);
		message++;
	}
	ft_send_byte('\0', pid);
	while (!g_ack_received)
		usleep(50);
	return (0);
}
