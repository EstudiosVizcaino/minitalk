/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvizcain <cvizcain@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 17:54:40 by cvizcain          #+#    #+#             */
/*   Updated: 2025/07/15 23:03:39 by cvizcain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minitalk.h"

// Justified global: holds all persistent state for the server, as signal
// handlers cannot be passed context directly.
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
 * Called after receiving 8 bits. Prints the character and resets the 
 * character buffer and bit index to prepare for the next incoming byte.
 */
static void	handle_completed_byte(void)
{
	ft_printf("%c", g_state.current_char);
	g_state.bit_index = 0;
	g_state.current_char = 0;
}

/**
 * @brief Main signal handler for the bonus server.
 * @param sig		Signal received (represents a bit).
 * @param info 		Struct containing the sender's PID.
 * @param ucontext	Unused.
 *
 * Reconstructs characters from bits sent via signals. When a null byte
 * (`'\0'`) is received, prints a newline, resets the state, and sends
 * a final acknowledgment (`SIGNAL_ACK_MSG`) to the client.
 * Also sends an acknowledgment for each bit (`SIGNAL_ACK_BIT`).
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
		{
			ft_printf("\n");
			kill(g_state.client_pid, SIGNAL_ACK_MSG);
			reset_state();
			return ;
		}
		else
			handle_completed_byte();
	}
	if (g_state.client_pid != 0)
		kill(g_state.client_pid, SIGNAL_ACK_BIT);
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
