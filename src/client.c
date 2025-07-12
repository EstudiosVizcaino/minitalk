#include "../includes/minitalk.h"

int	ft_send_byte(unsigned char byte, int pid)
{
	int	error;
	int	bit_count;

	error = 0;
	bit_count = 0;
	while (!error && bit_count < 8)
	{
		if ((byte & 0b10000000) == 0b10000000)
			error = kill(pid, SIGUSR2);
		else
			error = kill(pid, SIGUSR1);
		byte = byte << 1;
		bit_count++;
		usleep(500);
	}
	return (error);
}

int	main(int argc, char **argv)
{
	if (argc != 3)
		return (0);
	while (*argv[2])
	{
		if (ft_send_byte(*argv[2], ft_atoi(argv[1])) == -1)
			(write (2, "Error sending signal.\n", 22), exit (-1));
		argv[2]++;
		usleep(500);
	}
	if (ft_send_byte('\n', ft_atoi(argv[1])) == -1)
		(exit (-1));
}

