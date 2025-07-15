/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvizcain <cvizcain@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 17:54:40 by cvizcain          #+#    #+#             */
/*   Updated: 2025/07/15 22:58:22 by cvizcain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minitalk.h"

// Justified global: holds the client's PID across multiple signal handler
// calls, which is necessary to form a complete message.
static volatile t_server_state	g_state;

/**
 * @brief Resets the server's state to be ready for a new message.
 */
void	reset_state(void)
{
	g_state.current_char = 0;
	g_state.bit_index = 0;
	g_state.client_pid = 0;
}

/**
 * @brief Processes a fully received byte and resets the state for the next.
 *
 * This function is called once all 8 bits of a character have been
 * received. It prints the character and then clears the bit index and
 * character buffer to prepare for the next incoming byte.
 */
static void	handle_completed_byte(void)
{
	ft_printf("%c", g_state.current_char);
	g_state.bit_index = 0;
	g_state.current_char = 0;
}

/**
 * @brief Handles incoming signals to build characters bit by bit.
 *
 * @param sig      The received signal (bit 0 or bit 1).
 * @param info     Struct containing the sender's PID.
 * @param ucontext Not used.
 *
 * Reconstructs characters from signals, prints them when complete,
 * and sends back confirmation to the client.
 */
void	sig_handler(int sig, siginfo_t *info, void *ucontext)
{
	(void) ucontext;
	if (g_state.client_pid == 0)
		g_state.client_pid = info->si_pid;
	else if (g_state.client_pid != info->si_pid)
		return ;
	g_state.current_char = (g_state.current_char << 1) | (sig == SIGNAL_BIT_1);
	g_state.bit_index++;
	if (g_state.bit_index == BITS_IN_BYTE)
	{
		if (g_state.current_char == '\0')
			ft_printf("\n");
		else
			handle_completed_byte();
	}
	if (g_state.client_pid != 0)
		kill(g_state.client_pid, SIGNAL_ACK_BIT);
	if (g_state.current_char == '\0' && g_state.bit_index == BITS_IN_BYTE)
		reset_state();
}

/**
 * @brief Entry point of the server program.
 *
 * Sets up the signal handlers and begins waiting for incoming signals.
 * Prints the server's PID for client reference and enters an infinite
 * loop using `pause()` to idle until signals are received.
 *
 * @return Always returns 0 on successful execution.
 */
int	main(void)
{
	struct sigaction	sa;

	ft_printf("Server running with PID: %d\n", getpid());
	reset_state();
	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = sig_handler;
	sigemptyset(&sa.sa_mask);
	sigaddset(&sa.sa_mask, SIGNAL_BIT_0);
	sigaddset(&sa.sa_mask, SIGNAL_BIT_1);
	if (sigaction(SIGNAL_BIT_0, &sa, NULL) == -1
		|| sigaction(SIGNAL_BIT_1, &sa, NULL) == -1)
	{
		ft_printf("Error: Failed to register signal handlers.\n");
		exit(1);
	}
	while (1)
		pause();
	return (0);
}
