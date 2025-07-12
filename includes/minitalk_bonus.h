/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk_bonus.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvizcain <cvizcain@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 01:28:55 by cvizcain          #+#    #+#             */
/*   Updated: 2025/07/13 01:51:45 by cvizcain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_BONUS_H
# define MINITALK_BONUS_H

# include <unistd.h>
# include <stdlib.h>
# include <signal.h>
# include "../ft_printf/ft_printf.h"

typedef struct s_byte
{
	unsigned int	bit_num;
	unsigned char	byte;
}				t_byte;

int		ft_send_byte(unsigned char byte, int pid);
void	sigusr_handler(int sig, siginfo_t *info, void *ucontext);
void	sig_handler_client(int sig);

#endif