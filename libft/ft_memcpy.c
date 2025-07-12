/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvizcain <cvizcain@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 22:26:23 by cvizcain          #+#    #+#             */
/*   Updated: 2024/03/30 15:26:31 by cvizcain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	void	*temp;

	temp = dst;
	if (!dst && !src)
		return (temp);
	while (n--)
		*(char *)dst++ = *(char *)src++;
	return (temp);
}

/*int	main(void)
{
	printf("Outcome: %s\n", (char *)ft_memcpy("hola", "algo", 4));
	return (0);
}*/
