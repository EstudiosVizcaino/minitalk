/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvizcain <cvizcain@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 14:47:21 by cvizcain          #+#    #+#             */
/*   Updated: 2024/03/19 12:57:50 by cvizcain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isprint(int c)
{
	if (c >= 32 && c < 127)
		return (c);
	else
		return (0);
}

/*int main(void)
{
    int c;

    for (c = -128; c <= 127; c++)
    {
        if (ft_isprint(c))
            printf("'%c' es imprimible\n", c);
        else
            printf("'%d' no es imprimible\n", c);
    }

    return 0;
}
*/