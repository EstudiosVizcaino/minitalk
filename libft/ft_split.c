/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvizcain <cvizcain@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 17:54:59 by cvizcain          #+#    #+#             */
/*   Updated: 2025/04/08 04:15:32 by cvizcain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/// @brief Duplicates at most @p n characters from a string.
///
/// Allocates memory and copies at most @p n characters from @p s into a
/// new null-terminated string.
///
/// @param s The source string.
/// @param n The number of characters to duplicate.
/// @return A newly allocated string, or NULL if allocation fails or n == 0.
char	*ft_strndup(const char *s, size_t n)
{
	size_t	i;
	char	*str;

	i = 0;
	str = NULL;
	if (n == 0)
		return (NULL);
	str = (char *)malloc(sizeof(char) * (n + 1));
	if (str == 0)
		return (NULL);
	while (i < n)
	{
		str[i] = s[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

/// @brief Frees a null-terminated array of strings.
///
/// Iterates through each string in @p list and frees it, then frees
/// the array itself.
///
/// @param list The array of strings to free.
/// @return Always returns NULL.
char	**ft_free(char **list)
{
	size_t	j;

	j = 0;
	while (list[j])
	{
		free(list[j]);
		j++;
	}
	free(list);
	return (NULL);
}

/// @brief Counts the number of words in a string separated by a delimiter.
///
/// A word is defined as a sequence of characters not equal to @p c.
///
/// @param s The input string.
/// @param c The delimiter character.
/// @return The number of words found in the string.
size_t	ft_wordcount(char const *s, char c)
{
	size_t	wordcount;
	size_t	i;

	i = 0;
	wordcount = 0;
	while (s[i] != '\0')
	{
		if ((i == 0 && s[i] != c) || (s[i] == c
				&& s[i + 1] != '\0' && s[i + 1] != c))
			wordcount++;
		i++;
	}
	return (wordcount);
}

/// @brief Splits a string into an array of substrings using a delimiter.
///
/// Allocates and returns a null-terminated array of strings obtained by
/// splitting @p s using the character @p c as a delimiter.
///
/// @param s The string to split.
/// @param c The delimiter character.
/// @return A newly allocated array of strings, or NULL on failure.
char	**ft_split(char const *s, char c)
{
	char	**strlist;
	size_t	i;
	size_t	k;
	size_t	start_index;

	i = 0;
	k = 0;
	strlist = (char **)malloc(sizeof(char *) * (ft_wordcount(s, c) + 1));
	if (!strlist)
		return (NULL);
	while (i < ft_wordcount(s, c) && s[k])
	{
		while (s[k] == c)
			k++;
		start_index = k;
		while (s[k] != c && s[k])
			k++;
		strlist[i] = ft_strndup(&s[start_index], k - start_index);
		if (strlist[i++] == 0)
			return (ft_free(strlist));
	}
	strlist[i] = NULL;
	return (strlist);
}

/* 
int	main(void)
{
	char *str = "HOla!";
	char **s = ft_split(str, ' ');
	int i = 0;
	while (s[i])
		printf("Outcome: %s\n", s[i++]);
	return (0);
} */