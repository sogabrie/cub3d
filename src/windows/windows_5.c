/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   windows_5.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sogabrie <sogabrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 15:47:45 by sogabrie          #+#    #+#             */
/*   Updated: 2023/06/26 16:14:57 by sogabrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "windows.h"

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
