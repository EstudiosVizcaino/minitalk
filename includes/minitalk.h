/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvizcain <cvizcain@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 01:29:02 by cvizcain          #+#    #+#             */
/*   Updated: 2025/07/15 19:08:24 by cvizcain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# include <unistd.h>
# include <signal.h>
# include <sys/types.h>
# include <stdlib.h>
# include "../ft_printf/ft_printf.h"

// Define signals for clarity, making the code's intent self-documenting.
# define SIGNAL_BIT_0 SIGUSR1
# define SIGNAL_BIT_1 SIGUSR2

// Define acknowledgment signals for the bonus part.
# define SIGNAL_ACK_BIT SIGUSR1
# define SIGNAL_ACK_MSG SIGUSR2

// Using a macro for the number of bits in a byte is good practice.
# define BITS_IN_BYTE 8

/**
 * @struct t_server_state
 * @brief  Holds the persistent state of the bonus server.
 * @var    current_char The character currently being reconstructed from bits.
 * @var    bit_index    The count of bits received for the current character.
 * @var    client_pid   The PID of the client currently sending a message.
 */
typedef struct s_server_state
{
	unsigned char	current_char;
	int				bit_index;
	pid_t			client_pid;
}	t_server_state;

#endif
