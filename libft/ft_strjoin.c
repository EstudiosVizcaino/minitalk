/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvizcain <cvizcain@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 22:35:15 by cvizcain          #+#    #+#             */
/*   Updated: 2024/03/30 16:07:28 by cvizcain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	int		i;

	i = 0;
	str = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!str || !s1 || !s2)
		return (NULL);
	while (*s1)
		*(str + i++) = *s1++;
	while (*s2)
		*(str + i++) = *s2++;
	*(str + i) = '\0';
	return (str);
}
/* int	main(void)
{
	char const	*s1 = "hola";
	char const	*s2 = "Holita";
	printf("Outcome: %s", ft_strjoin(s1, s2));
} */