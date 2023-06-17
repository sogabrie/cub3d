#ifndef WINDOWS_H
# define WINDOWS_H

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

typedef struct s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

typedef struct s_param
{
	void			*mlx_ptr;
	void			*win_ptr;
	t_data			img;
    t_colors		col;
	double			x;
	double			y;
	t_data_segment	*data;
}					t_param;

int	creat_windows(t_data_segment *data);

#endif