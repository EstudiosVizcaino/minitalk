/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvizcain <cvizcain@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 01:29:15 by cvizcain          #+#    #+#             */
/*   Updated: 2025/07/16 17:29:09 by cvizcain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minitalk.h"

/// Global flag used to synchronize bit-by-bit communication with the server.
static volatile sig_atomic_t	g_server_ack = 0;

/**
 * @brief Signal handler for final message acknowledgment from the server.
 * @param sig Signal received (unused).
 *
 * This is a bonus feature. 
 * Receives a signal when the server confirms the full message was received.
 * The client prints a confirmation and exits cleanly.
 */
void	message_ack_handler(int sig)
{
	(void) sig;
	ft_printf("Server confirmed message receipt!\n");
	exit(0);
}

/**
 * @brief Signal handler for the server's bit-by-bit acknowledgment.
 * @param sig Signal received (unused).
 *
 * Crucial for synchronization. It sets a global flag, signaling that the server
 * has processed the last bit and the client can safely send the next one.
 */
void	ack_handler(int sig)
{
	(void) sig;
	g_server_ack = 1;
}

/**
 * @brief Sends one byte to the server, waiting for an ack for each bit.
 * @param byte	Byte to send.
 * @param pid	Server's Process ID.
 *
 * Sends each bit via a signal and waits for a confirmation signal
 * before sending the next one.
 * Includes a timeout mechanism to detect server failure or loss of sync.
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
				exit(1);
			}
			usleep(100);
		}
	}
}

/**
 * @brief Sets up the signal handlers for acknowledgments.
 *
 * This helper function configures and registers the two signal handlers
 * required for the bonus client: one for the bit-by-bit ack (SIGUSR1)
 * and one for the final message ack (SIGUSR2). It exits on failure.
 */
static void	setup_signal_handlers(void)
{
	struct sigaction	sa_bit_ack;
	struct sigaction	sa_msg_ack;

	sa_bit_ack.sa_handler = ack_handler;
	sigemptyset(&sa_bit_ack.sa_mask);
	sa_bit_ack.sa_flags = 0;
	if (sigaction(SIGNAL_ACK_BIT, &sa_bit_ack, NULL) == -1)
	{
		ft_printf("Error: Failed to register bit-ack handler.\n");
		exit(1);
	}
	sa_msg_ack.sa_handler = message_ack_handler;
	sigemptyset(&sa_msg_ack.sa_mask);
	sa_msg_ack.sa_flags = 0;
	if (sigaction(SIGNAL_ACK_MSG, &sa_msg_ack, NULL) == -1)
	{
		ft_printf("Error: Failed to register message-ack handler.\n");
		exit(1);
	}
}

/**
 * @brief The main function for the bonus client program.
 *
 * @param argc Argument count.
 * @param argv Argument vector: expects [Server PID] [Message].
 *
 * Delegates signal handler setup to a helper function. setup_signal_handlers()
 * Sends each character in the message, followed by a null byte to signal 
 * the end.
 *
 * @return 0 on success, 1 on incorrect usage.
 */
int	main(int argc, char **argv)
{
	int					server_pid;
	char				*message;

	if (argc != 3)
		return (ft_printf("Usage: ./client_bonus [Server PID] [Message]\n"), 1);
	setup_signal_handlers();
	server_pid = ft_atoi(argv[1]);
	message = argv[2];
	while (*message)
	{
		ft_send_byte(*message, server_pid);
		message++;
	}
	ft_send_byte('\0', server_pid);
	pause();
	return (0);
}
