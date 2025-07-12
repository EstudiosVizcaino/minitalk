/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvizcain <cvizcain@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 23:43:07 by cvizcain          #+#    #+#             */
/*   Updated: 2024/03/26 20:08:37 by cvizcain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	len;

	len = ft_strlen(src);
	while (dstsize > 1 && *src)
	{
		*(unsigned char *) dst++ = *(unsigned char *) src++;
		dstsize--;
	}
	if (dstsize)
		*(unsigned char *) dst = '\0';
	return (len);
}
/* int main() {
    char src[12] = "Hello, World!";
    char dst1[50];
    char dst2[50];

    size_t len1 = strlcpy(dst1, src, sizeof(dst1));
    size_t len2 = ft_strlcpy(dst2, src, sizeof(dst2));

    if (len1 != len2) {
        printf("Lengths do not match! strlcpy: %zu,ft_strlcpy: %zu\n"
			, len1, len2);
    } else if (strcmp(dst1, dst2) != 0) {
        printf("Copied strings do not match! strlcpy: %s, ft_strlcpy: %s\n", 
			dst1, dst2);
    } else {
        printf("Both functions produced the same result: %s\n", dst1);
    }

    return 0;
} */
