/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvizcain <cvizcain@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 19:07:15 by cvizcain          #+#    #+#             */
/*   Updated: 2024/04/12 13:52:03 by cvizcain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	void	*temp;

	temp = dst;
	if (!dst && !src)
		return (dst);
	if (dst == src)
		return (dst);
	if (dst > src)
	{
		while (len--)
			((char *)dst)[len] = ((char *)src)[len];
	}
	else
	{
		while (len--)
			*(unsigned char *)dst++ = *(unsigned char *)src++;
	}
	return (temp);
}
/*int main(void) 
{
    char src[50] = "This is the source string.";
    char dst1[50];
    char dst2[50];

    // Using original memmove
    memmove(dst1, src, strlen(src)+1);
    printf("Original memmove: %s\n", dst1);

    // Using your ft_memmove
    ft_memmove(dst2, src, strlen(src)+1);
    printf("Your ft_memmove: %s\n", dst2);

    return 0;
}*/