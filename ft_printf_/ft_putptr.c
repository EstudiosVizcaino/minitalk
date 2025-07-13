/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putptr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvizcain <cvizcain@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 17:22:53 by cvizcain          #+#    #+#             */
/*   Updated: 2024/09/01 21:49:38 by cvizcain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putptr_base(unsigned long int nbr, int *charcount)
{
	char				*base;
	unsigned int		base_len;

	base_len = 16;
	base = "0123456789abcdef";
	if (nbr < 16)
		ft_putchar(base[nbr % base_len], charcount);
	else
	{
		ft_putptr_base(nbr / base_len, charcount);
		ft_putptr_base(nbr % base_len, charcount);
	}
}

void	ft_putptr(void *nbr, int *charcount)
{
	unsigned long int	i;

	if (nbr == NULL)
	{
		ft_putstr("(nil)", charcount);
		return ;
	}
	else
	{
		i = (unsigned long int) nbr;
		ft_putstr("0x", charcount);
		ft_putptr_base(i, charcount);
	}
}
