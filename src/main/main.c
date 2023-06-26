/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sogabrie <sogabrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 16:13:41 by sogabrie          #+#    #+#             */
/*   Updated: 2023/06/26 16:24:22 by sogabrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
#include "windows.h"

int	main(int argc, char *argv[])
{
	t_data_segment	*data;

	data = (t_data_segment *)malloc(sizeof(t_data_segment));
	if (data == NULL)
	{
		exit(printf(E_MALLOC));
	}
	if (pars_part(argc, argv[1], &data))
	{
		return (1);
	}
	creat_windows(data);
	return (0);
}
