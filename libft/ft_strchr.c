/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvizcain <cvizcain@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 16:53:17 by cvizcain          #+#    #+#             */
/*   Updated: 2024/03/30 20:28:55 by cvizcain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	while (*s != (char) c && *s != '\0')
		++s;
	if (*s == (char)c)
		return ((char *) s);
	else
		return (NULL);
}
/* int	main(void)
{
	int			c = 65;
	const char	*s = "123asd 0aAs d";
	printf("Outcome: %s", ft_strchr(s, c));
	return (0);
} */