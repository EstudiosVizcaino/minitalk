/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvizcain <cvizcain@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 00:24:01 by cvizcain          #+#    #+#             */
/*   Updated: 2024/04/01 18:01:46 by cvizcain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_getnbr(int n, int nb, char *str)
{
	if (*str == '-')
	{
		str++;
		n--;
	}
	if (n--)
	{
		*(str + n) = (nb % 10) + 48;
		ft_getnbr(n, nb / 10, str);
	}
}

static int	ft_sizenumber(int nb)
{
	int	n;

	n = 0;
	if (nb < 0)
		nb *= -1;
	while (nb > 0)
	{
		nb /= 10;
		++n;
	}
	return (n);
}

char	*ft_itoa(int nb)
{
	char	*str;
	int		n;
	int		sign;

	sign = 1;
	if (nb == -2147483648)
		return (ft_strdup("-2147483648"));
	if (!nb)
		return (ft_strdup("0"));
	n = ft_sizenumber(nb);
	if (nb < 0)
	{
		nb *= -1;
		sign = -1;
		n++;
	}
	str = ft_calloc((n + 1), sizeof(char));
	if (!str)
		return (NULL);
	if (sign < 0)
		*str = '-';
	ft_getnbr(n, nb, str);
	*(str + n) = '\0';
	return (str);
}

/* int	main(void)
{
	int	n = 42;
	char	*s = ft_itoa(n);
	printf("Outcome: %s", s);
	free(s);
	system("leaks -q a.out");
} */
