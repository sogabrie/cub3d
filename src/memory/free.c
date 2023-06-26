/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sogabrie <sogabrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 16:13:45 by sogabrie          #+#    #+#             */
/*   Updated: 2023/06/26 16:13:46 by sogabrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	two_dimensional_mas(char ***str)
{
	size_t	i;

	i = 0;
	if (*str != NULL)
	{
		while ((*str)[i])
		{
			free((*str)[i]);
			i++;
		}
		free(*str);
		*str = NULL;
	}
}
