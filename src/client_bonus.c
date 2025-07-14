/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvizcain <cvizcain@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 01:29:15 by cvizcain          #+#    #+#             */
/*   Updated: 2025/07/14 19:29:07 by cvizcain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minitalk.h"

static t_client_state	g_client;

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

void	sig_handler_client(int sig)
{
	if (sig == SIGUSR2)
	{
		g_client.sig_counter++;
		g_client.ack_received = 1;
	}
}

static int	ft_send_byte(unsigned char byte, int pid)
{
	int	error;
	int	bit_count;

	error = 0;
	bit_count = 0;
	while (!error && bit_count < 8)
	{
		g_client.ack_received = 0;
		if ((byte & 0b10000000) == 0b10000000)
			error = kill(pid, SIGUSR2);
		else
			error = kill(pid, SIGUSR1);
		byte = byte << 1;
		bit_count++;
		while (!g_client.ack_received)
			usleep(100);
	}
	return (error);
}

int	main(int argc, char **argv)
{
	struct sigaction	action;

	g_client.sig_counter = 0;
	g_client.ack_received = 0;
	action.sa_handler = sig_handler_client;
	action.sa_flags = 0;
	sigemptyset(&action.sa_mask);
	if (argc != 3)
		return (ft_printf("Usage: ./client_bonus PID MESSAGE\n"), 0);
	if (sigaction(SIGUSR2, &action, NULL) == -1)
		(write(2, "Error receiving signal.\n", 14), exit (-1));
	while (*argv[2])
	{
		if (ft_send_byte(*argv[2], ft_atoi(argv[1])) == -1)
			(write (2, "Error sending signal.\n", 22), exit (-1));
		argv[2]++;
	}
	if (ft_send_byte('\0', ft_atoi(argv[1])) == -1)
		(write (2, "Error sending signal.\n", 22), exit (-1));
	ft_printf("Received %d signals from server corresponding to %d bytes.\n",
		g_client.sig_counter, g_client.sig_counter / 8);
}
