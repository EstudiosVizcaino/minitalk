/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvizcain <cvizcain@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 19:43:59 by cvizcain          #+#    #+#             */
/*   Updated: 2024/03/26 23:28:04 by cvizcain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	src_len;
	size_t	dst_len;
	size_t	n;

	src_len = ft_strlen(src);
	dst_len = ft_strlen(dst);
	n = 0;
	if (dstsize < dst_len + 1)
		return (src_len + dstsize);
	while (n < (dstsize - dst_len - 1) && *src)
		*(dst + dst_len + n++) = *src++;
	*(dst + dst_len + n) = '\0';
	return (src_len + dst_len);
}
/* 
int	main(void)
{
	char	dst[20];
	char	src[] = "aaa";
	printf("Outcome: %zu | %s", ft_strlcat(dst, src, 20), dst);
}   */