#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include "libft.h"
# include "def_struct.h"

//  42
# include <mlx.h>
// HOME
// # include "mlx.h"

//  Pars part
int		open_file(char *file_name);
int		check_cub(char *arg, char *cub);
void	color_options(char *options);
void	param_check(t_data_segment *data, char *str, int check[6], int status);
int		pars_map(char **map, int i, int j);
int		check_walls(char **map, int i, int j);
int		pars_part(int argc, char *argv, t_data_segment **data);

//  Pars utils
int		unprinted(char *str);
size_t	counts(char **map);
char	**optimisation_map(char **map);
int		divided_map(char **map);
int		check_map(char **map);
int		y_counts(char **map);
int		first_last_y(char *str);
int		max_x_axis(char **map);

//  Init struct
void	adding(t_colors *data, char **colors);
int		add_color(int num, int check[6], t_colors *color, char *options);
int		add_param(int num, int check[6], char **str, char *path);
void	save_parameters(int fd, t_data_segment *data);
void	save_map(int fd, t_data_segment *data);

//  Utils
int		check_end(int check[6]);
void	count_tmp(char **tmp);

//  Free functions
void	two_dimensional_mas(char ***str);

#endif