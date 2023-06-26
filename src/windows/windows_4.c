/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   windows_4.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sogabrie <sogabrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 15:47:37 by sogabrie          #+#    #+#             */
/*   Updated: 2023/06/26 15:58:22 by sogabrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "windows.h"

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