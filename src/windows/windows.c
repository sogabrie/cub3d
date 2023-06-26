/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   windows.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sogabrie <sogabrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 15:46:51 by sogabrie          #+#    #+#             */
/*   Updated: 2023/06/26 15:55:39 by sogabrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "windows.h"

int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

void	my_mlx_pixel_put(t_param *ptr, int x, int y, int color)
{
	char	*dst;

	if (x >= 0 && x < ptr->x && y >= 0 && y < ptr->y)
	{
		dst = ptr->img.addr + (y * ptr->img.line_length + x \
		* (ptr->img.bits_per_pixel / 8));
		*(unsigned int *)dst = color;
	}
}

int	ft_close(t_param *ptr)
{
	mlx_clear_window(ptr->mlx_ptr, ptr->win_ptr);
	mlx_destroy_image(ptr->mlx_ptr, ptr->img.img);
	mlx_destroy_window(ptr->mlx_ptr, ptr->win_ptr);
	exit(0);
	return (0);
}

void	create_c_f(t_param *ptr, int color, int start)
{
	int	i;
	int	k;

	i = 0;
	while (i < (ptr->y / 2))
	{
		k = 0;
		while (k < ptr->x)
		{
			my_mlx_pixel_put(ptr, k, start + i, color);
			k++;
		}
		i++;
	}
}

int	ft_isspace(char c)
{
	if (c == ' ' || (c >= 9 && c <= 13))
		return (1);
	return (0);
}

void	init2_str(t_param *ptr)
{
	ptr->ray.dir.x = 0;
	ptr->ray.dir.y = 0;
	ptr->ray.delta.x = 0;
	ptr->ray.delta.y = 0;
	ptr->ray.side.x = 0;
	ptr->ray.side.y = 0;
	ptr->ray.step_x = 0;
	ptr->ray.step_y = 0;
	ptr->ray.vert_hit = 0;
	ptr->ray.i = 0;
	ptr->plane.x = 0.66;
	ptr->plane.y = 0;
	ptr->wall.height = 0;
	ptr->wall.top = 0;
	ptr->wall.tex_x = 0;
	ptr->wall.tex_y = 0;
	ptr->wall.dist = 0;
}

void	init_str(t_param *ptr)
{
	ptr->pos_mous.x = ptr->x / 2;
	ptr->pos_mous.y = ptr->y / 2;
	ptr->map.no = NULL;
	ptr->map.so = NULL;
	ptr->map.we = NULL;
	ptr->map.ea = NULL;
	ptr->map.f = -1;
	ptr->map.c = -1;
	ptr->map.x = 0;
	ptr->map.y = 0;
	ptr->plr.pos.x = 0;
	ptr->plr.pos.y = 0;
	ptr->plr.dir.x = 0;
	ptr->plr.dir.y = 0;
	init2_str(ptr);
}

void	initcalizac(t_param *ptr)
{
	double	camera_x;

	camera_x = ptr->ray.i * 2.0 / (double)ptr->x - 1.0;
	ptr->ray.dir.x = ptr->plr.dir.x + ptr->plane.x * camera_x;
	ptr->ray.dir.y = ptr->plr.dir.y + ptr->plane.y * camera_x;
	ptr->map.x = (int)ptr->plr.pos.x;
	ptr->map.y = (int)ptr->plr.pos.y;
	ptr->ray.delta.x = fabs(1.0 / ptr->ray.dir.x);
	ptr->ray.delta.y = fabs(1.0 / ptr->ray.dir.y);
	ptr->ray.step_x = 1;
	ptr->ray.side.x = (ptr->map.x + 1.0 - ptr->plr.pos.x) * ptr->ray.delta.x;
	ptr->ray.step_y = 1;
	ptr->ray.side.y = (ptr->map.y + 1.0 - ptr->plr.pos.y) * ptr->ray.delta.y;
	if (ptr->ray.dir.x < 0)
	{
		ptr->ray.step_x = -1;
		ptr->ray.side.x = (ptr->plr.pos.x - ptr->map.x) * ptr->ray.delta.x;
	}
	if (ptr->ray.dir.y < 0)
	{
		ptr->ray.step_y = -1;
		ptr->ray.side.y = (ptr->plr.pos.y - ptr->map.y) * ptr->ray.delta.y;
	}
}

void	run(t_param *ptr)
{
	int	collision;

	collision = 0;
	while (!collision)
	{
		if (ptr->ray.side.x < ptr->ray.side.y)
		{
			ptr->ray.side.x += ptr->ray.delta.x;
			ptr->map.x += ptr->ray.step_x;
			ptr->ray.vert_hit = 0;
		}
		else
		{
			ptr->ray.side.y += ptr->ray.delta.y;
			ptr->map.y += ptr->ray.step_y;
			ptr->ray.vert_hit = 1;
		}
		if (ptr->data->map[(int)ptr->map.y][(int)ptr->map.x] == '1')
			collision = 1;
	}
}

void	calc_wall(t_param *ptr)
{
	if (!ptr->ray.vert_hit)
		ptr->wall.dist = ptr->ray.side.x - ptr->ray.delta.x;
	else
		ptr->wall.dist = ptr->ray.side.y - ptr->ray.delta.y;
	ptr->wall.height = (int)(ptr->y / ptr->wall.dist);
	ptr->wall.top = -ptr->wall.height / 2 + ptr->y / 2;
}

void	find_tex_x(t_param *ptr)
{
	double	wall_x;

	if (!ptr->ray.vert_hit)
		wall_x = ptr->plr.pos.y + ptr->wall.dist * ptr->ray.dir.y;
	else
		wall_x = ptr->plr.pos.x + ptr->wall.dist * ptr->ray.dir.x;
	wall_x -= floor(wall_x);
	ptr->wall.tex_x = (int)(wall_x * 64.0);
	if ((!ptr->ray.vert_hit && ptr->ray.dir.x > 0)
		|| (ptr->ray.vert_hit && ptr->ray.dir.y < 0))
		ptr->wall.tex_x = 64 - ptr->wall.tex_x - 1;
}

int	find(t_param *ptr, int x, int y)
{
	int	*tex;

	if (!ptr->ray.vert_hit)
	{
		if (ptr->ray.dir.x >= 0)
			tex = ptr->map.ea;
		else
			tex = ptr->map.we;
	}
	else
	{
		if (ptr->ray.dir.y >= 0)
			tex = ptr->map.so;
		else
			tex = ptr->map.no;
	}
	return (tex[64 * y + x]);
}

void	creat_line(t_param *ptr)
{
	double	scale;
	int		color;
	int		i;

	scale = 64.0 / (double)ptr->wall.height;
	ptr->wall.tex_y = 0;
	i = 0;
	while (i < ptr->wall.height)
	{
		color = find(ptr, ptr->wall.tex_x, (int)ptr->wall.tex_y);
		my_mlx_pixel_put(ptr, ptr->ray.i, ptr->wall.top + i, color);
		ptr->wall.tex_y += scale;
		i++;
	}
}

int	check_xpm(const char *line)
{
	int	i;
	int	fd;

	i = 0;
	if (!line)
		return (-1);
	while (line[i])
		i++;
	if (i < 5 || line[i - 1] != 'm' || line[i - 2] != 'p' || line[i - 3] != 'x'
		|| line[i - 4] != '.')
		return (-1);
	fd = open(line, O_RDONLY);
	if (fd < 0)
		return (-1);
	close(fd);
	return (0);
}

void	copy_texture(int **addr, void *tex_img)
{
	int	arg[3];
	int	*tmp;
	int	i;

	i = 0;
	tmp = (int *)mlx_get_data_addr(tex_img, &arg[0], &arg[1], &arg[2]);
	*addr = (int *)malloc(sizeof(int) * 4096);
	while (i < 4096)
	{
		(*addr)[i] = tmp[i];
		i++;
	}
}

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

void	move_left_right(int key, t_param *ptr)
{
	if (key == KEY_D)
	{
		if (ptr->data->map[(int)(ptr->plr.pos.y)]
			[(int)(ptr->plr.pos.x + ptr->plane.x * SPD_P)] == '0')
			ptr->plr.pos.x += ptr->plane.x * SPD_P;
		if (ptr->data->map[(int)(ptr->plr.pos.y + ptr->plane.y * SPD_P)]
			[(int)(ptr->plr.pos.x)] == '0')
			ptr->plr.pos.y += ptr->plane.y * SPD_P;
	}
	if (key == KEY_A)
	{
		if (ptr->data->map[(int)(ptr->plr.pos.y)]
			[(int)(ptr->plr.pos.x - ptr->plane.x * SPD_P)] == '0')
			ptr->plr.pos.x -= ptr->plane.x * SPD_P;
		if (ptr->data->map[(int)(ptr->plr.pos.y - ptr->plane.y * SPD_P)]
			[(int)(ptr->plr.pos.x)] == '0')
			ptr->plr.pos.y -= ptr->plane.y * SPD_P;
	}
}

void	rotation(int key, t_param *ptr, double rot)
{
	double	old_dirx;
	double	old_planex;

	old_dirx = ptr->plr.dir.x;
	old_planex = ptr->plane.x;
	if (key == LEFT)
	{
		ptr->plr.dir.x = ptr->plr.dir.x * cos(-rot)
			- ptr->plr.dir.y * sin(-rot);
		ptr->plr.dir.y = old_dirx * sin(-rot) + ptr->plr.dir.y * cos(-rot);
		ptr->plane.x = ptr->plane.x * cos(-rot) - ptr->plane.y * sin(-rot);
		ptr->plane.y = old_planex * sin(-rot) + ptr->plane.y * cos(-rot);
	}
	if (key == RIGHT)
	{
		ptr->plr.dir.x = ptr->plr.dir.x * cos(rot)
			- ptr->plr.dir.y * sin(rot);
		ptr->plr.dir.y = old_dirx * sin(rot) + ptr->plr.dir.y * cos(rot);
		ptr->plane.x = ptr->plane.x * cos(rot) - ptr->plane.y * sin(rot);
		ptr->plane.y = old_planex * sin(rot) + ptr->plane.y * cos(rot);
	}
}

int	deal_mous(int x, int y, t_param *ptr)
{
	int	key;

	(void)y;
	if (x < ptr->pos_mous.x && x < ptr->x / 2)
		key = LEFT;
	else if (x > ptr->pos_mous.x && x > ptr->x / 2)
		key = RIGHT;
	ptr->pos_mous.x = x;
	if (key == LEFT || key == RIGHT)
		rotation(key, ptr, SPD_R_M);
	return (0);
}

int	deal_key(int key, t_param *ptr)
{
	if (key == ESC)
		ft_close(ptr);
	else if (key == KEY_W || key == KEY_S)
		move_up_down(key, ptr);
	else if (key == KEY_A || key == KEY_D)
		move_left_right(key, ptr);
	else if (key == LEFT || key == RIGHT)
		rotation(key, ptr, SPD_R);
	return (0);
}

int	hooks(t_param *ptr)
{
	creat_wall(ptr);
	mlx_put_image_to_window(ptr->mlx_ptr, ptr->win_ptr, ptr->img.img, 0, 0);
	return (0);
}
/// @brief
/// @param ptr 
/// @param pov 
/// @param i 
/// @param k 
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
