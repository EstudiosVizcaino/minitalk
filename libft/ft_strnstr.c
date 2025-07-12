/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvizcain <cvizcain@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 20:31:49 by cvizcain          #+#    #+#             */
/*   Updated: 2024/03/26 17:02:40 by cvizcain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;

	if (!*needle)
		return ((char *) haystack);
	while (*haystack && len--)
	{
		i = 0;
		while (*(haystack + i) == *(needle + i) && *(needle + i)
			&& i <= len)
		{
			if (!*(needle + i + 1))
				return ((char *) haystack);
			++i;
		}
		haystack++;
	}
	return (NULL);
}
/*int	main(void)
{
	const char	*haystack = "askhdasdholasdadhola";
	const char *needle = "hola";
	printf("Outcome: %s", ft_strnstr(haystack, needle, 21));
}*/