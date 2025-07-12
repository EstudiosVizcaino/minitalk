/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvizcain <cvizcain@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 20:18:43 by cvizcain          #+#    #+#             */
/*   Updated: 2024/03/30 20:24:20 by cvizcain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (*s != '\0')
	{
		++s;
		++i;
	}
	if (c > 256)
		c -= 256;
	if (*s == (char) c)
		return ((char *) s);
	while (i >= 0)
	{
		if (*s == (char) c)
			return ((char *)s);
		--i;
		--s;
	}
	return (NULL);
}
/* int	main(void)
{
	//int			c = 123;
	const char	*s = "123456789";
	printf("Outcome: %s", ft_strrchr(s, 49));
	return (0);
} */