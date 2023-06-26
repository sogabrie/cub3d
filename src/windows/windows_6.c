/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   windows_6.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sogabrie <sogabrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 15:47:49 by sogabrie          #+#    #+#             */
/*   Updated: 2023/06/26 16:24:34 by sogabrie         ###   ########.fr       */
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
