/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvizcain <cvizcain@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 17:54:40 by cvizcain          #+#    #+#             */
/*   Updated: 2025/07/12 23:36:00 by cvizcain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minitalk.h"
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void handler(int signalnum, siginfo_t *info, void *context)
{
	(void)info;
	static int	pos;
	static char	xar;
	static int	state = 0;
	(void)context; // evitamos warning si no usamos

	state = 1;
	if (signalnum == SIGUSR1)
		xar |= (1 << pos);  // bit a 1
	// SIGUSR2: no cambia el bit → queda en 0

	pos++;
	if (pos == 8)
	{
		write(1, &xar, 1); // imprime el char recibido
		pos = 0;
		xar = 0;
	}

	// Opcional: ACK al cliente
	kill(info->si_pid, SIGUSR1); // enviar señal de vuelta si quieres sincronización
	state = 0;
}


int main()
{
	struct sigaction sa;


	printf("Mandatory Server is running - PID: %d\n", getpid());

	sa.sa_sigaction = handler;        // usa el handler con 3 argumentos
	sigemptyset(&sa.sa_mask);         // no bloqueamos otras señales durante el handler
	sa.sa_flags = SA_SIGINFO;         // necesario para recibir info como el PID del cliente

	sigaction(SIGUSR1, &sa, NULL);    // registrar SIGUSR1
	sigaction(SIGUSR2, &sa, NULL);    // registrar SIGUSR2

	while (1)
		pause();  // espera señales

	return (0);
}
