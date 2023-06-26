/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   windows_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sogabrie <sogabrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 15:47:22 by sogabrie          #+#    #+#             */
/*   Updated: 2023/06/26 16:14:44 by sogabrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "windows.h"

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
