#include "cub3D.h"

int	y_counts(char **map)
{
	int	count;

	count = 0;
	while (map[count])
		count++;
	return (count);
}

int	first_last_y(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		if (!ft_strchr(" 1\n", str[i]))
			return (1);
	return (0);
}

int	check_walls(char **map, int i, int j)
{
	if (map[i + 1][j] == ' ' || map[i + 1][j] == '\n'
		|| map[i + 1][j] == '\0')
		return (1);
	if (map[i - 1][j] == ' ' || map[i - 1][j] == '\n'
		|| map[i - 1][j] == '\0')
		return (1);
	if (map[i][j + 1] == ' ' || map[i][j + 1] == '\n'
		|| map[i][j + 1] == '\0')
		return (1);
	if (map[i][j - 1] == ' ' || map[i][j - 1] == '\n'
		|| map[i][j - 1] == '\0')
			return (1);
	return (0);
}

int	pars_map(char **map)
{
	int	count;
	int	i;
	int	j;

	i = -1;
	j = -1;
	count = y_counts(map);
	if (first_last_y(map[0]) || first_last_y(map[count - 1]))
		return (1);
	while (++i < count - 1)
	{
		while (map[i][++j])
		{
			if (!ft_strchr("10 NSEWD\n", map[i][j]))
				return (1);
			if (ft_strchr("0NSEWD", map[i][j]) && check_walls(map, i, j))
				return (1);
		}
		j = -1;
	}
	return (0);
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
	if (pars_map((*data)->map))
		exit(printf(E_MAP_CONF));
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
	system("leaks cub3D");
	printf("data.options.north_texture = %s\n", data->options.north_texture);
	printf("data.options.south_texture = %s\n", data->options.south_texture);
	printf("data.options.west_texture = %s\n", data->options.west_texture);
	printf("data.options.east_texture = %s\n", data->options.east_texture);
	printf("floor : %d %d %d\n", data->options.floor.red, data->options.floor.green, data->options.floor.blue);
	printf("ceiling : %d %d %d\n", data->options.ceiling.red, data->options.ceiling.green, data->options.ceiling.blue);
	for(int i = 0; data->map[i]; i++)
		printf("%s", data->map[i]);
	return (0);
}
