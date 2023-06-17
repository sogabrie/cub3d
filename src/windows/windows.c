#include "windows.h"

int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

int	ft_close(t_param *ptr)
{
	mlx_clear_window(ptr->mlx_ptr, ptr->win_ptr);
	mlx_destroy_image(ptr->mlx_ptr, ptr->img.img);
	mlx_destroy_window(ptr->mlx_ptr, ptr->win_ptr);
	exit(0);
	return (0);
}

int	deal_mous(int key, int x, int y, t_param *ptr)
{
	printf("maus key = %d X = %d Y = %d\n",key, x, y);
	my_mlx_pixel_put(&(ptr->img), x, y, \
			create_trgb(1, 255, 255, 255));
	mlx_put_image_to_window(ptr->mlx_ptr, ptr->win_ptr, ptr->img.img, 0, 0);
	return (0);
}

int	deal_key(int key, t_param *ptr)
{
	printf("maus key = %d\n",key);
	if (key == 53)
		ft_close(ptr);
	return (0);
}


void	create_c_f(t_param *ptr, int color, int start)
{
	int	i;
	int	k;

	i = 0;
	while (i < (ptr->y  / 2))
	{
		k = 0;
		while (k < ptr->x)
		{
			my_mlx_pixel_put(&(ptr->img), k, start + i, color);
			k++;
		}
		i++;
	}
}

///
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

void run(t_param *ptr)
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
		my_mlx_pixel_put(&(ptr->img), ptr->ray.i, ptr->wall.top + i, color);
		ptr->wall.tex_y += scale;
		i++;
	}
}

///

int creat_wall(t_param *ptr)
{
	int	i = 0;
	create_c_f(ptr, create_trgb(1, ptr->data->options.ceiling.red, ptr->data->options.ceiling.green, ptr->data->options.ceiling.blue), 0);
	create_c_f(ptr, create_trgb(1, ptr->data->options.floor.red, ptr->data->options.floor.green, ptr->data->options.floor.blue), ptr->y / 2);

	while (i < ptr->x)
	{
		initcalizac(ptr);
		run(ptr);
		calc_wall(ptr);
		find_tex_x(ptr);
		creat_line(ptr);
		++i;
	}

	mlx_put_image_to_window(ptr->mlx_ptr, ptr->win_ptr, ptr->img.img, 0, 0);
	return (0);
}

int	hooks(t_param *ptr)
{
	//  t_param *ptr = pt;
	// mlx_mouse_hook(ptr->win_ptr, deal_mous, ptr);
	ptr->data->options.ceiling.red = (ptr->data->options.ceiling.red + 50) % 255;
	ptr->data->options.ceiling.green = (ptr->data->options.ceiling.green + 50) % 255;
	ptr->data->options.ceiling.blue = (ptr->data->options.ceiling.blue + 50) % 255;

	ptr->data->options.floor.red = (ptr->data->options.floor.red + 50) % 255;
	ptr->data->options.floor.green = (ptr->data->options.floor.green + 50) % 255;
	ptr->data->options.floor.blue = (ptr->data->options.floor.blue + 50) % 255;

	creat_wall(ptr);
	mlx_key_hook(ptr->win_ptr, deal_key, ptr);
	mlx_hook(ptr->win_ptr, 17, 1L << 17, ft_close, ptr);
	// mlx_loop(ptr->mlx_ptr);
	return (0);
}

int	creat_windows(t_data_segment *data)
{
    t_param	ptr;
    ptr.x = 2000;
    ptr.y = 1000;
	ptr.data = data;

	ptr.mlx_ptr = mlx_init();
	ptr.win_ptr = mlx_new_window(ptr.mlx_ptr, ptr.x, ptr.y, "cub3D");
	ptr.img.img = mlx_new_image(ptr.mlx_ptr, ptr.x, ptr.y);
	ptr.img.addr = mlx_get_data_addr(ptr.img.img, &(ptr.img.bits_per_pixel), \
					&(ptr.img.line_length), &(ptr.img.endian));
	
	// hooks(&ptr);
	mlx_loop_hook( ptr.mlx_ptr, hooks, &ptr);
	mlx_loop(ptr.mlx_ptr);
	ft_close(&ptr);

    return (0);
}