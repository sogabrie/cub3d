/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   windows.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sogabrie <sogabrie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 15:54:25 by sogabrie          #+#    #+#             */
/*   Updated: 2023/06/26 16:00:20 by sogabrie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WINDOWS_H
# define WINDOWS_H

# define SPD_P 0.6
# define SPD_R 0.2
# define SPD_R_M 0.03
# define ESC 53
# define KEY_W 13
# define KEY_A 0
# define KEY_S 1
# define KEY_D 2
# define LEFT 123
# define RIGHT 124

# include <string.h>
# include <mlx.h>
# include <errno.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <math.h>
# include "cub3D.h"
# include "def_struct.h"

typedef struct s_map
{
	int				*no;
	int				*so;
	int				*we;
	int				*ea;
	int				*an1;
	int				f;
	int				c;
	int				x;
	int				y;
}					t_map;

typedef struct s_point
{
	double			x;
	double			y;
}					t_point;

typedef struct 		s_player {
	t_point			pos;
	t_point			dir;
}					t_player;

typedef struct s_ray
{
	t_point			dir;
	t_point			delta;
	t_point			side;
	int				i;
	int				step_x;
	int				step_y;
	int				vert_hit;
}					t_ray;

typedef struct s_data
{
	void			*img;
	char			*addr;
	int				bits_per_pixel;
	int				line_length;
	int				endian;
}					t_data;

typedef struct s_wall
{
	int				height;
	int				top;
	int				tex_x;
	double			tex_y;
	double			dist;
}					t_wall;

typedef struct s_param
{
	void			*mlx_ptr;
	void			*win_ptr;
	t_data			img;
    t_colors		col;
	t_point			wind;
	t_point			pos_mous;
	t_map			map;
	double			x;
	double			y;
	t_wall			wall;
	t_ray			ray;
	t_player		plr;
	t_point			plane;
	t_data_segment	*data;
}					t_param;


int		create_trgb(int t, int r, int g, int b);
void	my_mlx_pixel_put(t_param *ptr, int x, int y, int color);
int		ft_close(t_param *ptr);
void	create_c_f(t_param *ptr, int color, int start);
int		ft_isspace(char c);
void	init2_str(t_param *ptr);
void	init_str(t_param *ptr);
void	initcalizac(t_param *ptr);
void	run(t_param *ptr);
void	calc_wall(t_param *ptr);
void	find_tex_x(t_param *ptr);
int		find(t_param *ptr, int x, int y);
void	creat_line(t_param *ptr);
int		check_xpm(const char *line);
void	copy_texture(int **addr, void *tex_img);
int		parse_texture(t_param *ptr, int **addr, char *line, int i);
void	draw_point(t_param *ptr, int color, int x, int y);
void	minimap(t_param *ptr);
int		creat_wall(t_param *ptr);
void	move_up_down(int key, t_param *ptr);
void	move_left_right(int key, t_param *ptr);
void	rotation(int key, t_param *ptr, double rot);
int		deal_mous(int x, int y, t_param *ptr);
int		deal_key(int key, t_param *ptr);
int		hooks(t_param *ptr);
void	set_direction(t_param *ptr, char pov, double i, double k);
int		set_position(t_param *ptr);
int		creat_windows(t_data_segment *data);

#endif