/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvizcain <cvizcain@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 01:29:02 by cvizcain          #+#    #+#             */
/*   Updated: 2025/07/15 18:51:58 by cvizcain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# include <unistd.h>
# include <signal.h>
# include <sys/types.h>
# include <stdlib.h>
# include "../ft_printf/ft_printf.h"

typedef struct s_server_state
{
	unsigned char	current_char;
	int				bit_index;
	pid_t			client_pid;
}	t_server_state;

#endif