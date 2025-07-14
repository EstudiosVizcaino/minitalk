/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvizcain <cvizcain@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 20:03:25 by cvizcain          #+#    #+#             */
/*   Updated: 2024/08/28 15:03:53 by cvizcain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	ft_write(char c, int *charcount)
{
	*charcount += write (1, &c, 1);
}

static void	ft_getnbr(int nb, int *charcount)
{
	if (nb > 9)
		ft_getnbr(nb / 10, charcount);
	ft_write(((nb % 10) + 48), charcount);
}

void	ft_putnbr(int nb, int *charcount)
{
	if (nb < 0)
	{
		ft_write('-', charcount);
		if (nb == -2147483648)
		{
			ft_write('2', charcount);
			nb = -147483648;
		}
		nb *= -1;
		ft_getnbr(nb, charcount);
	}
	else
	{
		ft_getnbr(nb, charcount);
	}
}
