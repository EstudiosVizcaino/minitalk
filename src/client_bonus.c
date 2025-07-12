/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvizcain <cvizcain@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 01:29:15 by cvizcain          #+#    #+#             */
/*   Updated: 2025/07/13 01:51:09 by cvizcain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minitalk_bonus.h"

static int	g_sig_counter;

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

int	main(int argc, char **argv)
{
	struct sigaction	action;

	action.sa_handler = sig_handler_client;
	if (argc != 3)
		return (ft_printf("Usage: ./client PID MESSAGE\n"), 0);
	if (sigaction(SIGUSR2, &action, NULL) == -1)
		(write(2, "Error receiving signal.\n", 14), exit (-1));
	while (*argv[2])
	{
		if (ft_send_byte(*argv[2], ft_atoi(argv[1])) == -1)
			(write (2, "Error sending signal.\n", 22), exit (-1));
		argv[2]++;
		usleep(500);
	}
	if (ft_send_byte('\n', ft_atoi(argv[1])) == -1)
		(write (2, "Error sending signal.\n", 22), exit (-1));
	ft_printf("Received %d signals from server corresponding to \
%d bytes.\n", g_sig_counter, g_sig_counter / 8);
}

void	sig_handler_client(int sig)
{
	if (sig)
	{
		g_sig_counter++;
		usleep(100);
	}
	return ;
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
		usleep (500);
	}
	return (error);
}