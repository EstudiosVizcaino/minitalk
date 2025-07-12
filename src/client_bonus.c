#include "../includes/minitalk.h"

static sig_atomic_t g_ack_received = 0;

void ack_handler(int sig)
{
	(void)sig;
	g_ack_received = 1;
}


void wait_for_ack(void)
{
	while (!g_ack_received)
		pause();  // espera activamente
	g_ack_received = 0;
}
void	xartosignal(char xar, int pid)
{
	int	bit = 0;

	while (bit < 8)
	{
		if ((xar >> bit) & 1)
			kill(pid, SIGUSR1);  // bit = 1
		else
			kill(pid, SIGUSR2);  // bit = 0
		wait_for_ack();          // espera confirmación
		bit++;
	}
}

int	main(int argc, char **argv)
{
	int		i;
	int		pid;
	char	*str;
	struct sigaction sa_ack;

	sa_ack.sa_handler = ack_handler;
	sigemptyset(&sa_ack.sa_mask);
	sa_ack.sa_flags = 0;
	sigaction(SIGUSR1, &sa_ack, NULL);
	if (argc != 3)
	{
		printf("Client must have a PID and a msg!\n");
		return (0);
	}
	pid = ft_atoi(*(argv + 1));
	str = *(argv + 2);
	printf("Mandatory Client:  PID: %d, MSG: %s\n", pid, str);
	i = 0;
	while (*(str + i))
	{
		xartosignal(*(str + i), pid);
		i++;
	}
	return (0);
}