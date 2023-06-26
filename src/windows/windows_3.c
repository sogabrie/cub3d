/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   windows_3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sogabrie <sogabrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 15:47:32 by sogabrie          #+#    #+#             */
/*   Updated: 2023/06/26 16:14:48 by sogabrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "windows.h"

int	parse_texture(t_param *ptr, int **addr, char *line, int i)
{
	void	*tex_img;
	int		arg[2];

	if (check_xpm(line))
		return (-1);
	tex_img = mlx_xpm_file_to_image(ptr->mlx_ptr, line, &arg[0], &arg[1]);
	if (arg[0] != 64 || arg[1] != 64 || !tex_img)
	{
		if (tex_img)
			mlx_destroy_image(ptr->mlx_ptr, tex_img);
		return (-1);
	}
	copy_texture(addr, tex_img);
	mlx_destroy_image(ptr->mlx_ptr, tex_img);
	return (1);
}

void	draw_point(t_param *ptr, int color, int x, int y)
{
	int	start_x;
	int	start_y;

	start_y = y;
	while (start_y < 12 + y)
	{
		start_x = x;
		while (start_x < 12 + x)
		{
			my_mlx_pixel_put(ptr, start_x, start_y, color);
			start_x++;
		}
		start_y++;
	}
}

void	minimap(t_param *ptr)
{
	int	i;
	int	k;
	int	color;

	i = -1;
	while (ptr->data->map[++i])
	{
		k = -1;
		while (ptr->data->map[i][++k])
		{
			if (ptr->data->map[i][k] == '0')
			{
				color = 0xFFFFFF;
				draw_point(ptr, color, k * 12, i * 12);
			}
			if (ptr->data->map[i][k] == '1')
			{
				color = 0x000000;
				draw_point(ptr, color, k * 12, i * 12);
			}
		}
	}
	draw_point(ptr, 0xFF0000,
		(int)ptr->plr.pos.x * 12, (int)ptr->plr.pos.y * 12);
}

int	creat_wall(t_param *ptr)
{
	ptr->ray.i = 0;
	create_c_f(ptr, create_trgb(1, ptr->data->options.ceiling.red, \
	ptr->data->options.ceiling.green, ptr->data->options.ceiling.blue), 0);
	create_c_f(ptr, create_trgb(1, ptr->data->options.floor.red, \
	ptr->data->options.floor.green, ptr->data->options.floor.blue), ptr->y / 2);
	while (ptr->ray.i < ptr->x)
	{
		initcalizac(ptr);
		run(ptr);
		calc_wall(ptr);
		find_tex_x(ptr);
		creat_line(ptr);
		++ptr->ray.i;
	}
	minimap(ptr);
	return (0);
}

void	move_up_down(int key, t_param *ptr)
{
	if (key == KEY_W)
	{
		if (ptr->data->map[(int)(ptr->plr.pos.y)]
			[(int)(ptr->plr.pos.x + ptr->plr.dir.x * SPD_P)] == '0')
			ptr->plr.pos.x += ptr->plr.dir.x * SPD_P;
		if (ptr->data->map[(int)(ptr->plr.pos.y + ptr->plr.dir.y * SPD_P)]
			[(int)(ptr->plr.pos.x)] == '0')
			ptr->plr.pos.y += ptr->plr.dir.y * SPD_P;
	}
	if (key == KEY_S)
	{
		if (ptr->data->map[(int)(ptr->plr.pos.y)]
			[(int)(ptr->plr.pos.x - ptr->plr.dir.x * SPD_P)] == '0')
			ptr->plr.pos.x -= (ptr->plr.dir.x * SPD_P);
		if (ptr->data->map[(int)(ptr->plr.pos.y - ptr->plr.dir.y * SPD_P)]
			[(int)(ptr->plr.pos.x)] == '0')
			ptr->plr.pos.y -= (ptr->plr.dir.y * SPD_P);
	}
}
