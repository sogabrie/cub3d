#include "cub3D.h"

int	unprinted(char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (!((str[i] >= 0 && str[i] <= 32) || (str[i] == 127)))
			return (0);
		i++;
	}
	return (1);
}

size_t	counts(char **map)
{
	size_t	size;
	size_t	size_new;

	size = 0;
	size_new = 0;
	while (map[size])
	{
		if (!unprinted(map[size]))
			size_new++;
		size++;
	}
	return (size_new);
}

char	**optimisation_map(char **map)
{
	char	**new_map;
	size_t	size;
	size_t	size_new;

	size_new = counts(map);
	new_map = malloc(sizeof(char *) * (size_new + 1));
	if (new_map == NULL)
		exit(printf(E_CONFIGURATION));
	size = 0;
	size_new = 0;
	while (map[size])
	{
		if (!unprinted(map[size]))
			new_map[size_new++] = map[size];
		else
			free(map[size]);
		size++;
	}
	new_map[size_new] = NULL;
	free(map);
	return (new_map);
}

int	divided_map(char **map)
{
	size_t	start;

	start = 0;
	while (unprinted(map[start]))
		start++;
	while (map[start])
	{
		if (!unprinted(map[start]))
			start++;
		else
			break ;
	}
	while (map[start])
	{
		if (unprinted(map[start]))
			start++;
		else
			break ;
	}
	if (map[start] != NULL)
		return (1);
	return (0);
}

void	save_map(int fd, t_data_segment *data)
{
	size_t	i;
	char	**new_map;
	char	**map;

	i = 0;
	map = NULL;
	while (1)
	{
		new_map = malloc(sizeof(char *) * (i + 2));
		if (new_map == NULL)
			exit(printf(E_MALLOC));
		new_map[i + 1] = NULL;
		map = ft_strcat(map, new_map, i);
		map[i] = get_next_line(fd);
		printf("%s\n", map[i]);
		if (map[i] == NULL)
			break ;
		i++;
	}
	// Segmentation ..
	// ..
	if (divided_map(map))
		exit(printf(E_CONFIGURATION));
	map = optimisation_map(map);
	data->map = map;
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
	// .. 
	// pars_map ..
	// ..
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
	// printf("data.options.north_texture = %s\n", data->options.north_texture);
	// printf("data.options.south_texture = %s\n", data->options.south_texture);
	// printf("data.options.west_texture = %s\n", data->options.west_texture);
	// printf("data.options.east_texture = %s\n", data->options.east_texture);
	// printf("floor : %d %d %d\n", data->options.floor.red, data->options.floor.green, data->options.floor.blue);
	// printf("ceiling : %d %d %d\n", data->options.ceiling.red, data->options.ceiling.green, data->options.ceiling.blue);
	// for(int i = 0; data->map[i]; i++)
	// 	printf("%s", data->map[i]);
	return (0);
}
