#include "cub3D.h"

void	save_parameters(int fd, t_data_segment *data)
{
	char		*tmp;
	static int	check[6];

	while (!check_end(check))
	{	
		tmp = get_next_line(fd);
		if (tmp == NULL)
			break ;
		if (tmp[0] == '\n')
		{
			free(tmp);
			continue ;
		}
		param_check(data, tmp, check, 0);
		free(tmp);
	}
	// if (!check_end(check))
	// 	exit(printf(E_CONFIGURATION));
	// ..
	// wait..
	// Create map..
	// ..
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
	close(fd);
	return (0);
}

int	main(int argc, char *argv[])
{
	t_data_segment	*data;

	data = (t_data_segment *)malloc(sizeof(t_data_segment));
	if (data == NULL)
		exit(printf(E_MALLOC));
	if (pars_part(argc, argv[1], &data))
		return (1);
	// system("leaks cub3D");
	// printf("data.options.north_texture = %s", data->options.north_texture);
	// printf("data.options.south_texture = %s", data->options.south_texture);
	// printf("data.options.west_texture = %s", data->options.west_texture);
	// printf("data.options.east_texture = %s", data->options.east_texture);
	// printf("floor : %d %d %d\n", data->options.floor.red, data->options.floor.green, data->options.floor.blue);
	// printf("ceiling : %d %d %d\n", data->options.ceiling.red, data->options.ceiling.green, data->options.ceiling.blue);
	return (0);
}
