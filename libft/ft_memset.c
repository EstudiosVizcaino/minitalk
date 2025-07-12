/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvizcain <cvizcain@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 21:01:43 by cvizcain          #+#    #+#             */
/*   Updated: 2024/03/20 00:02:41 by cvizcain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	void	*temp;

	temp = b;
	while (len--)
		*(unsigned char *)b++ = (unsigned char)c;
	return (temp);
}
/*int	main(void)
{
	char buffer[10];
	printf("Outcome: %s",(char *)ft_memset(buffer, 65, 4));
	return (0);
}*/