/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr_strlen.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aafrikya <aafrikya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 16:42:00 by aafrikya          #+#    #+#             */
/*   Updated: 2023/06/26 16:42:01 by aafrikya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr_strlen(const char *big, const char *lit, size_t len)
{
	size_t	i;
	size_t	l;
	size_t	f;
	char	*bi;

	bi = (char *)big;
	l = ft_strlen(lit);
	if (bi == lit || l == 0)
		return (bi);
	if (!len)
		return (0);
	i = 0;
	while (bi[i] != 0 && i < len)
	{
		f = 0;
		while (bi[i + f] != 0 && bi[i + f] == lit[f] && \
				lit[f] != 0 && (i + f) < len)
			++f;
		if (f == l)
			return (bi + i + ft_strlen(lit));
		++i;
	}
	return (0);
}
