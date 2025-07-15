/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvizcain <cvizcain@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 01:29:02 by cvizcain          #+#    #+#             */
/*   Updated: 2025/07/15 12:47:18 by cvizcain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# include <unistd.h>
# include <signal.h>
# include <sys/types.h>
# include <stdlib.h>
# include "../ft_printf/ft_printf.h"

typedef struct s_client_state
{
	int						sig_counter;
	volatile sig_atomic_t	ack_received;
}	t_client_state;

#endif