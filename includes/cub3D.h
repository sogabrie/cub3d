#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include "libft.h"

//  42
// # include <mlx.h>
// HOME
# include "mlx.h"

# define E_MALLOC "Error\n! Failed to allocate dynamic memory !\n"
# define E_ARGC_1 "Error\n! Please specify the .cub file !\n"
# define W_ARGC_2 "Warning\n! Only the first argument is considered !\n"
# define E_OPEN_FILE "Error\n! It was not possible to open the file !\n"
# define E_FILE_EMPTY "Error\n! .cub file is empty !\n"
# define E_CONFIGURATION "Error\n! wrong file configuration !\n"

//  Pars part
int	open_file(char *file_name);
int	check_cub(char *arg, char *cub);

#endif