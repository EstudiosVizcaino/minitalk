/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvizcain <cvizcain@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 06:10:15 by cvizcain          #+#    #+#             */
/*   Updated: 2024/03/20 06:20:45 by cvizcain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	while (n--)
	{
		if (*(unsigned char *) s == (unsigned char) c)
			return ((void *)s);
		++s;
	}
	return (NULL);
}
/*int	main(void)
{
	printf("Outcome: %s\n", (char *) ft_memchr("hola", 'o', 4));
	return (0);
}*/