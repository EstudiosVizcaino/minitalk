/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvizcain <cvizcain@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 22:48:50 by cvizcain          #+#    #+#             */
/*   Updated: 2024/03/30 22:31:32 by cvizcain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	start;
	size_t	end;

	if ((!*s1 && !*set) || (!*s1 && *set))
		return (ft_strdup(""));
	start = 0;
	end = ft_strlen(s1);
	while (*set && ft_strchr(set, *(s1 + start)))
		++start;
	while (ft_strchr(set, *(s1 + end - 1)))
		--end;
	return (ft_substr(s1, start, end - start));
}
/* int main (void)
{
	char *str = "hohohoholaohohohho";
	char *set = "ho";
	printf("Outcome: %s\n", ft_strtrim(str, set));
	return (0);
} */