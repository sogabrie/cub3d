#include "cub3D.h"

int	open_file(char *file_name)
{
	int	fd;

	fd = open(file_name, O_RDONLY);
	if (fd < 0)
		exit(printf(E_OPEN_FILE));
	return (fd);
}

int	check_cub(char *arg, char *cub)
{
	size_t	len_arg;
	size_t	len_cub;

	len_arg = ft_strlen(arg);
	len_cub = ft_strlen(cub);
	if (len_arg == len_cub)
		return (1);
	while (len_cub > 0)
	{
		--len_arg;
		--len_cub;
		if (arg[len_arg] != cub[len_cub])
			return (1);
	}
	return (0);
}

void	color_options(char *options)
{
	int	i;
	int	count;

	i = -1;
	count = 0;
	if (options == NULL)
		exit(printf(E_CONFIGURATION));
	while (options[++i])
	{
		if (options[i] == ',' && options[i + 1] != '\n')
		{
			count++;
			continue ;
		}
		if (!ft_isdigit(options[i]) && options[i + 1] != '\0')
			exit(printf(E_CONFIGURATION));
	}
	if (count != 2)
		exit(printf(E_CONFIGURATION));
}

void	param_check(t_data_segment *data, char *str, int check[6], int status)
{
	char	**tmp;

	tmp = ft_split(str, ' ');
	count_tmp(tmp);
	if (tmp == NULL || tmp[0] == NULL)
		exit(printf(E_MALLOC));
	if (ft_strcmp(tmp[0], "NO") == 0 && check[0] != 1)
		status = add_param(0, check, &(data->options.north_texture), tmp[1]);
	if (ft_strcmp(tmp[0], "SO") == 0 && check[1] != 1)
		status = add_param(1, check, &(data->options.south_texture), tmp[1]);
	if (ft_strcmp(tmp[0], "WE") == 0 && check[2] != 1)
		status = add_param(2, check, &(data->options.west_texture), tmp[1]);
	if (ft_strcmp(tmp[0], "EA") == 0 && check[3] != 1)
		status = add_param(3, check, &(data->options.east_texture), tmp[1]);
	if (ft_strcmp(tmp[0], "F") == 0 && check[4] != 1)
		status = add_color(4, check, &(data->options.floor), tmp[1]);
	if (ft_strcmp(tmp[0], "C") == 0 && check[5] != 1)
		status = add_color(5, check, &(data->options.ceiling), tmp[1]);
	if (status != 1)
	{
		two_dimensional_mas(&tmp);
		exit(printf(E_CONFIGURATION));
	}
	two_dimensional_mas(&tmp);
}

int	pars_part(int argc, char *argv, t_data_segment **data)
{
	int	fd;

	if (argc == 1 || check_cub(argv, ".cub"))
		return (printf(E_ARGC_1));
	if (argc > 2)
		printf(W_ARGC_2);
	fd = open_file(argv);
	save_parameters(fd, *data);
	save_map(fd, *data);
	if (pars_map((*data)->map, -1, -1))
		exit(printf(E_MAP_CONF));
	(*data)->y_axis = y_counts((*data)->map);
	(*data)->x_axis = max_x_axis((*data)->map);
	close(fd);
	return (0);
}
