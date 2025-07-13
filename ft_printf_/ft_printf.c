/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvizcain <cvizcain@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 09:04:18 by cvizcain          #+#    #+#             */
/*   Updated: 2024/09/01 22:23:55 by cvizcain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_switch(const char *s, va_list	*list, int *charcount)
{
	if (*s == 's')
		ft_putstr(va_arg(*list, char *), charcount);
	if (*s == 'c')
		ft_putchar(va_arg(*list, int), charcount);
	if (*s == 'i' || *s == 'd')
		ft_putnbr(va_arg(*list, int), charcount);
	if (*s == 'u')
		ft_putdecun(va_arg(*list, int), charcount);
	if (*s == 'p')
		ft_putptr(va_arg(*list, void *), charcount);
	if (*s == 'x')
		ft_putnbr_hexa(va_arg(*list, size_t), 'x', charcount);
	if (*s == 'X')
		ft_putnbr_hexa(va_arg(*list, size_t), 'X', charcount);
	if (*s == '%')
		ft_putchar('%', charcount);
}

int	ft_printf(const char *s, ...)
{
	va_list	list;
	int		charcount;

	charcount = 0;
	va_start(list, s);
	while (*s)
	{
		if (*s == '%')
		{
			s++;
			ft_switch(s, &list, &charcount);
		}
		else
		{
			charcount += write (1, s, 1);
		}
		s++;
	}
	va_end(list);
	return (charcount);
}
