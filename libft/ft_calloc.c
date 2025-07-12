/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvizcain <cvizcain@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 22:41:51 by cvizcain          #+#    #+#             */
/*   Updated: 2024/04/01 21:45:02 by cvizcain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*buffer;
	void	*buffer_cpy;

	if (count != 0 && ((SIZE_MAX / count) < size))
		return (NULL);
	buffer = malloc(count * size);
	if (!buffer)
		return (NULL);
	buffer_cpy = buffer;
	count *= size;
	while (count--)
		*(unsigned char *) buffer++ = 0;
	return (buffer_cpy);
}
/*int main() {
    size_t nmemb = 10;
    size_t size = sizeof(int);

    int *original_calloc = calloc(nmemb, size);
    int *ft_calloc_result = ft_calloc(nmemb, size);

    if (original_calloc == NULL || ft_calloc_result == NULL) {
        printf("Memory allocation failed.\n");
        return 1;
    }

    // Fill the memory with some data
    for (size_t i = 0; i < nmemb; i++) {
        original_calloc[i] = i;
        ft_calloc_result[i] = i;
    }

    // Compare the two memory areas
    if (memcmp(original_calloc, ft_calloc_result, nmemb * size) == 0) {
        printf("ft_calloc works correctly.\n");
    } else {
        printf("ft_calloc does not work correctly.\n");
    }

    free(original_calloc);
    free(ft_calloc_result);

    return 0;
}*/
