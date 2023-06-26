/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aafrikya <aafrikya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 16:42:02 by aafrikya          #+#    #+#             */
/*   Updated: 2023/06/26 16:42:03 by aafrikya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*a;
	char	*a1;

	a = (char *) s;
	a1 = (char *) 0;
	while (*a != 0)
	{
		if (*a == (unsigned char)c)
			a1 = a;
		++a;
	}
	if ((unsigned char)c == 0)
		a1 = a;
	return (a1);
}
