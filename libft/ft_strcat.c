/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aafrikya <aafrikya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 16:41:41 by aafrikya          #+#    #+#             */
/*   Updated: 2023/06/26 16:41:42 by aafrikya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_strcat(char **map, char **new_map, size_t i)
{
	size_t	j;

	j = 0;
	if (map == NULL)
		return (new_map);
	while (j <= i && map[j] != NULL)
	{
		new_map[j] = map[j];
		j++;
	}
	free(map);
	return (new_map);
}
