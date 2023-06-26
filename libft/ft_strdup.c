/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aafrikya <aafrikya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 16:41:50 by aafrikya          #+#    #+#             */
/*   Updated: 2023/06/26 16:41:51 by aafrikya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	size_t	l;
	char	*ptr;

	l = ft_strlen(s) + 1;
	ptr = (char *)malloc(l);
	if (!ptr)
		return (0);
	ft_strlcpy(ptr, s, l);
	return (ptr);
}
