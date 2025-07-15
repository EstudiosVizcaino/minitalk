/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvizcain <cvizcain@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 01:29:02 by cvizcain          #+#    #+#             */
/*   Updated: 2025/07/15 23:27:30 by cvizcain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# include <unistd.h>
# include <signal.h>
# include <sys/types.h>
# include <stdlib.h>
# include "../ft_printf/ft_printf.h"

/// Signal representing a binary 0 bit from client to server.
# define SIGNAL_BIT_0 SIGUSR1

/// Signal representing a binary 1 bit from client to server.
# define SIGNAL_BIT_1 SIGUSR2

/// Signal used by the server to acknowledge receipt of a bit.
# define SIGNAL_ACK_BIT SIGUSR1

/// Signal used by the server to acknowledge full message receipt.
# define SIGNAL_ACK_MSG SIGUSR2

/// Number of bits in a byte (8 bits).
# define BITS_IN_BYTE 8

/**
 * @struct t_server_state
 * @brief  Stores the server's progress during message reconstruction.
 * 
 * This structure is required for storing persistent data across multiple
 * signal handler calls. It stores the partial character being built,
 * the number of bits received so far, and the PID of the client.
 */
typedef struct s_server_state
{
	unsigned char	current_char;
	int				bit_index;
	pid_t			client_pid;
}	t_server_state;

#endif
