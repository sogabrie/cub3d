/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aafrikya <aafrikya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 16:41:48 by aafrikya          #+#    #+#             */
/*   Updated: 2023/06/26 16:41:49 by aafrikya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	s;

	s = 0;
	while (s1[s] != '\0' || s2[s] != '\0')
	{
		if (s1[s] != s2[s])
			return (1);
		++s;
	}
	if (s1[s] == '\0' && s2[s] == '\0')
		return (0);
	return (1);
}
