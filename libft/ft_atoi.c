/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvizcain <cvizcain@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 19:33:08 by cvizcain          #+#    #+#             */
/*   Updated: 2025/07/12 18:15:15 by cvizcain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/// @brief Determines the sign of a number from a string.
/// @param str A pointer to the current character in the string.
/// @return -1 if the character is '-', 1 if '+', and 0 otherwise.
static int	ft_getsign(const char *str)
{
	if (*str == '-')
		return (-1);
	else if (*str == '+')
		return (1);
	else
		return (0);
}

/// @brief Converts a string to an integer, handling optional
/// whitespace and sign.
///        If overflow occurs, an error is printed and 0 is returned.
/// @param str The input string to convert.
/// @return The resulting integer, or 0 if overflow is detected
int	ft_atoi(const char *str)
{
	long	nb;
	int		sign;

	nb = 0;
	sign = 1;
	while (*str && ((*str >= 9 && *str <= 13) || *str == 32))
		str++;
	sign = ft_getsign(str);
	if (sign != 0)
		str++;
	else
		sign = 1;
	while (*str && (*str >= 48 && *str <= 57))
	{
		nb = nb * 10 + (*str++ - 48);
		if ((sign == 1 && nb > INT_MAX) || (sign == -1 && - nb < INT_MIN))
		{
			write(1, "Error\n", 6);
			return (-1);
		}
	}
	return ((int)(nb * sign));
}
/*int	main(void)
{
	printf("Outcome: %i, %s\n", ft_atoi("1231230023adas23"), "1231230023adas23");
}*/