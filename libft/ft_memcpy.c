/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aafrikya <aafrikya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 16:41:33 by aafrikya          #+#    #+#             */
/*   Updated: 2023/06/26 16:41:34 by aafrikya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *a, const void *b, size_t s)
{
	size_t	i;

	if (!a && !b)
		return (0);
	i = 0;
	while (i < s)
	{
		((unsigned char *)a)[i] = ((unsigned char *)b)[i];
		++i;
	}
	return (a);
}
