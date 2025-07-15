/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvizcain <cvizcain@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 01:29:20 by cvizcain          #+#    #+#             */
/*   Updated: 2025/07/15 20:59:08 by cvizcain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minitalk.h"

static volatile sig_atomic_t	g_server_ack = 1;

static int	ft_atoi(const char *str)
{
	int		sign;
	long	nbr;

	sign = 1;
	nbr = 0;
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '-')
		sign = -1;
	if (*str == '-' || *str == '+')
		str++;
	while (*str >= '0' && *str <= '9')
	{
		nbr = nbr * 10 + (*str - '0');
		str++;
	}
	return ((int)(nbr * sign));
}

/**
 * @brief Handler for the server's bit-by-bit acknowledgment.
 * @param sig The signal number received (unused).
 *
 * This handler is crucial for synchronization. It sets a global flag,
 * signaling that the server has processed the last bit and the client
 * can safely send the next one.
 */
void	ack_handler(int sig)
{
	(void) sig;
	g_server_ack = 1;
}

/**
 * @brief Sends one byte to the server, waiting for an ack for each bit.
 * @param byte The byte to send.
 * @param pid The server's Process ID.
 *
 * This function implements a robust, synchronized protocol. It sends one
 * bit and then waits for the server's acknowledgment before proceeding.
 * It includes a timeout to prevent an infinite loop if the server stops
 * responding.
 */
void	ft_send_byte(unsigned char byte, int pid)
{
	int	bits_to_send;
	int	timeout;

	bits_to_send = BITS_IN_BYTE;
	while (bits_to_send--)
	{
		g_server_ack = 0;
		if ((byte >> bits_to_send) & 1)
			kill(pid, SIGNAL_BIT_1);
		else
			kill(pid, SIGNAL_BIT_0);
		timeout = 0;
		while (!g_server_ack)
		{
			if (timeout++ > 200)
			{
				ft_printf("Error: No response from server.\n");
				exit (1);
			}
			usleep(100);
		}
	}
}

/**
 * @brief The main function for the client program.
 *
 * It validates arguments, sets up the signal handler, and sends the
 * message from the command line to the specified server PID, character
 * by character, followed by a null terminator.
 */
int	main(int argc, char **argv)
{
	int		server_pid;
	char	*message;

	if (argc != 3)
		return (ft_printf("Usage: ./client [Server PID] [Message]\n"), 1);
	signal(SIGNAL_ACK_BIT, ack_handler);
	server_pid = ft_atoi(argv[1]);
	message = argv[2];
	while (*message)
	{
		ft_send_byte(*message, server_pid);
		message++;
	}
	ft_send_byte('\0', server_pid);
	while (!g_server_ack)
		usleep(50);
	return (0);
}
