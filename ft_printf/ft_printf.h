/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvizcain <cvizcain@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 16:38:48 by cvizcain          #+#    #+#             */
/*   Updated: 2025/07/16 16:57:53 by cvizcain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <unistd.h>
# include <stdarg.h>

int		ft_printf(const char *s, ...);
void	ft_putchar(int c, int *charcount);
void	ft_putdecun(int nbr, int *charcount);
void	ft_putptr(void *nbr, int *charcount);
void	ft_putstr(char *s, int *charcount);
int		ft_strlen(char *s);
void	ft_putnbr(int nb, int *charcount);
void	ft_putnbr_hexa(unsigned int nbr, char base, int *charcount);
int		ft_atoi(const char *str);

#endif
