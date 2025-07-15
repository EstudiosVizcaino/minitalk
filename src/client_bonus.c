/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvizcain <cvizcain@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 01:29:15 by cvizcain          #+#    #+#             */
/*   Updated: 2025/07/15 17:37:13 by cvizcain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minitalk.h"

static volatile sig_atomic_t	g_ack_received = 0;

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

// Handler for the bit-by-bit acknowledgment from the server.
void	bit_ack_handler(int sig)
{
	(void)sig;
	g_ack_received = 1;
}

// Handler for the final message acknowledgment (BONUS feature).
void	message_ack_handler(int sig)
{
	(void) sig;
	ft_printf("Server successfully received the full message!\n");
	exit(0);
}

// Sends one byte, waiting for an acknowledgment for each bit.
void	ft_send_byte(unsigned char byte, int pid)
{
	int	i;

	i = 8;
	while (i--)
	{
		g_ack_received = 0; // Reset flag before sending.
		if ((byte >> i) & 1)
			kill(pid, SIGUSR2); // Bit '1'
		else
			kill(pid, SIGUSR1); // Bit '0'
		
		// Wait for the server to send back SIGUSR1, confirming receipt.
		// A timeout is added to prevent infinite loops if the server dies.
		int timeout = 0;
		while (!g_ack_received)
		{
			if (timeout++ > 1000) // Timeout after ~100ms
			{
				ft_printf("Error: No response from server.\n");
				exit(1);
			}
			usleep(100);
		}
	}
}

int	main(int argc, char **argv)
{
	int					pid;
	char				*message;
	struct sigaction	sa_bit_ack;
	struct sigaction	sa_msg_ack;

	if (argc != 3)
		return (ft_printf("Usage: ./client_bonus [PID] [MESSAGE]\n"), 1);
	sa_bit_ack.sa_handler = bit_ack_handler;
	sigemptyset(&sa_bit_ack.sa_mask);
	sa_bit_ack.sa_flags = 0;
	sigaction(SIGUSR1, &sa_bit_ack, NULL);
	sa_msg_ack.sa_handler = message_ack_handler;
	sigemptyset(&sa_msg_ack.sa_mask);
	sa_msg_ack.sa_flags = 0;
	sigaction(SIGUSR2, &sa_msg_ack, NULL);
	pid = ft_atoi(argv[1]);
	message = argv[2];
	while (*message)
	{
		ft_send_byte(*message, pid);
		message++;
	}
	ft_send_byte('\0', pid);
	pause();
	return (0);
}
