/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvizcain <cvizcain@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 17:45:49 by cvizcain          #+#    #+#             */
/*   Updated: 2024/04/01 21:30:38 by cvizcain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_write(char c, int fd)
{
	write (fd, &c, 1);
}

void	ft_getnbr(int nb, int fd)
{
	if (nb > 9)
		ft_getnbr(nb / 10, fd);
	ft_write((nb % 10) + 48, fd);
}

void	ft_putnbr_fd(int nb, int fd)
{
	if (nb < 0)
	{
		ft_write('-', fd);
		if (nb == -2147483648)
		{
			ft_write('2', fd);
			nb = -147483648;
		}
		nb *= -1;
		ft_getnbr(nb, fd);
	}
	else
	{
		ft_getnbr(nb, fd);
	}
}
