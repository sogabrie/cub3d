/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aafrikya <aafrikya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 16:41:31 by aafrikya          #+#    #+#             */
/*   Updated: 2023/06/26 16:41:32 by aafrikya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*a;
	size_t			i;
	unsigned char	c2;

	i = 0;
	c2 = (unsigned char)c;
	a = (unsigned char *) s;
	while (i < n)
	{
		if (*a == c2)
			return (a);
		++a;
		++i;
	}
	return (0);
}
