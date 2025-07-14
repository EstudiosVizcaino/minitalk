/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putdecun.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvizcain <cvizcain@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 17:24:16 by cvizcain          #+#    #+#             */
/*   Updated: 2024/09/01 22:26:54 by cvizcain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	ft_write(char c, int *charcount)
{
	*charcount += write (1, &c, 1);
}

static void	ft_getnbr(unsigned int nbr, int *charcount)
{
	if (nbr > 9)
		ft_getnbr(nbr / 10, charcount);
	ft_write(((nbr % 10) + 48), charcount);
}

void	ft_putdecun(int nbr, int *charcount)
{
	unsigned int	u;

	u = 0;
	if (nbr < 0)
	{
		u = (nbr + 4294967296);
		ft_getnbr(u, charcount);
	}
	else
		ft_getnbr(nbr, charcount);
}
