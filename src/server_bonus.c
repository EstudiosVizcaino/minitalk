/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvizcain <cvizcain@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 17:54:40 by cvizcain          #+#    #+#             */
/*   Updated: 2025/07/15 17:38:36 by cvizcain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minitalk.h"

// This struct cleanly holds all state variables.
// The global variable is justified because signal handlers cannot take extra parameters.
typedef struct s_server_state
{
	unsigned char	current_char;
	int				bit_index;
	pid_t			client_pid;
}	t_server_state;

static volatile t_server_state g_state;

// Resets the server state to be ready for a new message.
void	reset_state(void)
{
	g_state.current_char = 0;
	g_state.bit_index = 0;
	g_state.client_pid = 0;
}

// The core logic handler.
void	sig_handler(int sig, siginfo_t *info, void *ucontext)
{
	(void) ucontext;
	// Lock onto the client PID for the duration of one message.
	if (g_state.client_pid == 0)
		g_state.client_pid = info->si_pid;
	// If a signal from a different client arrives, ignore it.
	else if (g_state.client_pid != info->si_pid)
		return;

	// Reconstruct the character bit by bit.
	g_state.current_char = (g_state.current_char << 1) | (sig == SIGUSR2);
	g_state.bit_index++;
	
	// Acknowledge the received bit immediately.
	kill(g_state.client_pid, SIGUSR1);

	// If a full byte (8 bits) has been received.
	if (g_state.bit_index == 8)
	{
		// If the byte is the null terminator, the message is complete.
		if (g_state.current_char == '\0')
		{
			ft_printf("\n");
			// BONUS: Send a final acknowledgment for the whole message.
			kill(g_state.client_pid, SIGUSR2);
			reset_state(); // Reset for the next message.
		}
		else
		{
			ft_printf("%c", g_state.current_char);
			// Reset for the next byte.
			g_state.bit_index = 0;
			g_state.current_char = 0;
		}
	}
}

int	main(void)
{
	struct sigaction	sa;

	ft_printf("Server PID: %d\n", getpid());
	reset_state();
	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = sig_handler;
	sigemptyset(&sa.sa_mask);
	sigaddset(&sa.sa_mask, SIGUSR1);
	sigaddset(&sa.sa_mask, SIGUSR2);
	if (sigaction(SIGUSR1, &sa, NULL) == -1 || sigaction(SIGUSR2, &sa, NULL) == -1)
	{
		ft_printf("Error: Signal registration failed.\n");
		exit(1);
	}
	while (1)
		pause();
	return (0);
}