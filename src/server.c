/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvizcain <cvizcain@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 17:54:40 by cvizcain          #+#    #+#             */
/*   Updated: 2025/07/12 23:51:18 by cvizcain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minitalk.h"
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>



void	sigusr_handler(int sig)
{
	static unsigned char	byte;
	static unsigned int		bit_num;

	byte = byte << 1;
	if (sig == SIGUSR2)
		byte |= 1;
	bit_num++;
	if (bit_num == 8)
	{
		printf("%c", byte);
		byte = 0;
		bit_num = 0;
	}
}

int	main(void)
{
	struct sigaction	action;

	printf("PID: %d\n", getpid());
	action.sa_handler = sigusr_handler;
	if (sigaction(SIGUSR1, &action, NULL) == -1)
		(write(2, "Signal error.\n", 14), exit (-1));
	if (sigaction(SIGUSR2, &action, NULL) == -1)
		(write(2, "signal error.\n", 14), exit (-1));
	while (1)
	{
		pause();
	}
}
