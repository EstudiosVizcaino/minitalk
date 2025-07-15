/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvizcain <cvizcain@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 17:54:40 by cvizcain          #+#    #+#             */
/*   Updated: 2025/07/15 12:47:22 by cvizcain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minitalk.h"

static volatile pid_t	g_client_pid = 0;

static void	handle_completed_byte(unsigned char *byte, int *bit_index)
{
	if (*byte == '\0')
	{
		ft_printf("\n");
		kill(g_client_pid, SIGUSR1);
		g_client_pid = 0;
	}
	else
	{
		ft_printf("%c", *byte);
	}
	*byte = 0;
	*bit_index = 0;
}

void	sig_handler(int sig, siginfo_t *info, void *ucontext)
{
	static unsigned char	current_char = 0;
	static int				bit_index = 0;

	(void) ucontext;
	if (g_client_pid == 0)
		g_client_pid = info->si_pid;
	else if (info->si_pid != g_client_pid)
		return ;
	current_char = (current_char << 1) | (sig == SIGUSR2);
	bit_index++;
	if (bit_index == 8)
		handle_completed_byte(&current_char, &bit_index);
	if (g_client_pid)
		kill(g_client_pid, SIGUSR1);
}

int	main(void)
{
	struct sigaction	sa;

	ft_printf("Server PID: %d\n", getpid());
	sigemptyset(&sa.sa_mask);
	sigaddset(&sa.sa_mask, SIGUSR1);
	sigaddset(&sa.sa_mask, SIGUSR2);
	sa.sa_sigaction = sig_handler;
	sa.sa_flags = SA_SIGINFO;
	if (sigaction(SIGUSR1, &sa, NULL) == -1
		|| sigaction(SIGUSR2, &sa, NULL) == -1)
	{
		ft_printf("Signal registration error.\n");
		exit(1);
	}
	while (1)
		pause();
	return (0);
}
