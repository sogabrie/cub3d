#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include "libft.h"
# include "def_struct.h"

//  42
// # include <mlx.h>
// HOME
# include "mlx.h"

//  Pars part
int		open_file(char *file_name);
int		check_cub(char *arg, char *cub);
void	color_options(char *options);
void	param_check(t_data_segment *data, char *str, int check[6], int status);

//  Init struct
void	adding(t_colors *data, char **colors);
int		add_color(int num, int check[6], t_colors *color, char *options);
int		add_param(int num, int check[6], char **str, char *path);

//  Utils
int		check_end(int check[6]);
void	count_tmp(char **tmp);

//  Free functions
void	two_dimensional_mas(char ***str);

#endif