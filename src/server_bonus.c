/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvizcain <cvizcain@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 17:54:40 by cvizcain          #+#    #+#             */
/*   Updated: 2025/07/15 12:47:33 by cvizcain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minitalk.h"

static volatile pid_t	g_client_pid = 0;

char	ft_guarrada(void)
{
	g_client_pid = 0;
	return ('\n');
}

void	sigusr_handler(int sig, siginfo_t *info, void *ucontext)
{
	static unsigned char	byte;
	static unsigned int		bit_num;

	(void) ucontext;
	if (g_client_pid == 0)
		g_client_pid = info->si_pid;
	else if (g_client_pid != info->si_pid)
		return ;
	byte = byte << 1;
	if (sig == SIGUSR2)
		byte |= 1;
	bit_num++;
	if (kill(info->si_pid, SIGUSR2) == -1)
		(ft_printf("Error sending signal to client.\n"), exit (-1));
	if (bit_num == 8)
	{
		if (byte == '\0')
			ft_printf("%c", ft_guarrada());
		else
			ft_printf("%c", byte);
		byte = 0;
		bit_num = 0;
	}
}

int	main(void)
{
	struct sigaction	action;

	ft_printf("PID: %d\n", getpid());
	action.sa_flags = SA_SIGINFO;
	action.sa_sigaction = sigusr_handler;
	sigemptyset(&action.sa_mask);
	sigaddset(&action.sa_mask, SIGUSR1);
	sigaddset(&action.sa_mask, SIGUSR2);
	if (sigaction(SIGUSR1, &action, NULL) == -1)
		(write(2, "Signal error.\n", 14), exit (-1));
	if (sigaction(SIGUSR2, &action, NULL) == -1)
		(write(2, "signal error.\n", 14), exit (-1));
	while (1)
	{
		pause();
	}
}
