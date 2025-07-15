/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvizcain <cvizcain@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 17:54:40 by cvizcain          #+#    #+#             */
/*   Updated: 2025/07/15 18:52:37 by cvizcain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minitalk.h"

static volatile t_server_state	g_state;

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
	if (g_state.client_pid == 0)
		g_state.client_pid = info->si_pid;
	else if (g_state.client_pid != info->si_pid)
		return ;
	g_state.current_char = (g_state.current_char << 1) | (sig == SIGUSR2);
	g_state.bit_index++;
	kill(g_state.client_pid, SIGUSR1);
	if (g_state.bit_index == 8)
	{
		if (g_state.current_char == '\0')
		{
			ft_printf("\n");
			kill(g_state.client_pid, SIGUSR2);
			reset_state();
		}
		else
		{
			ft_printf("%c", g_state.current_char);
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
	if (sigaction(SIGUSR1, &sa, NULL) == -1
		|| sigaction(SIGUSR2, &sa, NULL) == -1)
	{
		ft_printf("Error: Signal registration failed.\n");
		exit(1);
	}
	while (1)
		pause();
	return (0);
}
