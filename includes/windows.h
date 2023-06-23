#ifndef WINDOWS_H
# define WINDOWS_H

// # define SPD_P 0.6
// # define SPD_R 0.2
// # define SPD_R_M 0.1
// # define ESC 53
// # define KEY_W 119
// # define KEY_A 97
// # define KEY_S 115
// # define KEY_D 100
// # define LEFT 65361
// # define RIGHT 65363

# define SPD_P 0.6
# define SPD_R 0.2
# define SPD_R_M 0.05
# define ESC 53
# define KEY_W 13
# define KEY_A 0
# define KEY_S 1
# define KEY_D 2
# define LEFT 123
# define RIGHT 124

# include <string.h>
# include <mlx.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <math.h>
#include "cub3D.h"
#include "def_struct.h"

typedef struct s_map
{
	int		*no;
	int		*so;
	int		*we;
	int		*ea;
	int		f;
	int		c;
	int		x;
	int		y;
}				t_map;

typedef struct s_point
{
	double	x;
	double	y;
}				t_point;

typedef struct s_player {
	t_point	pos;
	t_point	dir;
}				t_player;

typedef struct s_ray
{
	t_point	dir;
	t_point	delta;
	t_point	side;
	int		i;
	int		step_x;
	int		step_y;
	int		vert_hit;
}				t_ray;

typedef struct s_data
{
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
}				t_data;

typedef struct s_wall
{
	int		height;
	int		top;
	int		tex_x;
	double	tex_y;
	double	dist;
}				t_wall;

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

int	creat_windows(t_data_segment *data);

#endif