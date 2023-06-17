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


void	ft_create(t_param *ptr, int color, int start)
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

int creat_wall(t_param *ptr)
{
	ft_create(ptr, create_trgb(1, ptr->data->options.ceiling.red, ptr->data->options.ceiling.green, ptr->data->options.ceiling.blue), 0);
	ft_create(ptr, create_trgb(1, ptr->data->options.floor.red, ptr->data->options.floor.green, ptr->data->options.floor.blue), ptr->y / 2);

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