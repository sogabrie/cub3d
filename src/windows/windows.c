/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   windows.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sogabrie <sogabrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 15:46:51 by sogabrie          #+#    #+#             */
/*   Updated: 2023/06/26 15:58:11 by sogabrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "windows.h"

void	set_direction(t_param *ptr, char pov, double i, double k)
{
	ptr->plr.pos.x = k + 0.5;
	ptr->plr.pos.y = i + 0.5;
	if (pov == 'E')
	{
		ptr->plr.dir.x = 1;
		ptr->plane.x = 0;
		ptr->plane.y = 0.66;
	}
	else if (pov == 'W')
	{
		ptr->plr.dir.x = -1;
		ptr->plane.x = 0;
		ptr->plane.y = -0.66;
	}
	else if (pov == 'S')
	{
		ptr->plr.dir.y = 1;
		ptr->plane.x = -0.66;
	}
	else if (pov == 'N')
		ptr->plr.dir.y = -1;
}

int	set_position(t_param *ptr)
{
	double		i;
	double		k;
	char		pov;
	int			count;

	i = -1;
	count = 0;
	while (ptr->data->map[(int)++i])
	{
		k = -1;
		while (ptr->data->map[(int)i][(int)++k])
		{
			pov = ptr->data->map[(int)i][(int)k];
			if (pov == 'N' || pov == 'S' || pov == 'W' || pov == 'E')
			{
				if (count++)
					return (-1);
				set_direction(ptr, pov, i, k);
				ptr->data->map[(int)i][(int)k] = '0';
			}
		}
	}
	if (!count)
		return (-1);
	return (0);
}

int	creat_windows(t_data_segment *data)
{
	t_param	ptr;

	ptr.x = 1000;
	ptr.y = 500;
	ptr.data = data;
	ptr.mlx_ptr = mlx_init();
	ptr.win_ptr = mlx_new_window(ptr.mlx_ptr, ptr.x, ptr.y, "cub3D");
	ptr.img.img = mlx_new_image(ptr.mlx_ptr, ptr.x, ptr.y);
	ptr.img.addr = mlx_get_data_addr(ptr.img.img, &(ptr.img.bits_per_pixel), \
					&(ptr.img.line_length), &(ptr.img.endian));
	init_str(&ptr);
	set_position(&ptr);
	parse_texture(&ptr, &ptr.map.no, data->options.east_texture, 0);
	parse_texture(&ptr, &ptr.map.so, data->options.north_texture, 0);
	parse_texture(&ptr, &ptr.map.ea, data->options.south_texture, 0);
	parse_texture(&ptr, &ptr.map.we, data->options.west_texture, 0);
	mlx_loop_hook(ptr.mlx_ptr, hooks, &ptr);
	mlx_hook(ptr.win_ptr, 2, 1L << 0, &deal_key, &ptr);
	mlx_hook(ptr.win_ptr, 6, 1L << 0, &deal_mous, &ptr);
	mlx_hook(ptr.win_ptr, 17, 1L << 17, ft_close, &ptr);
	mlx_loop(ptr.mlx_ptr);
	ft_close(&ptr);
	return (0);
}
