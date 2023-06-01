#include "cub3D.h"

void	adding(t_colors *data, char **colors)
{
	data->red = ft_atoi(colors[0]);
	if (!(data->red <= 255 && data->red >= 0))
		exit(printf(E_CONFIGURATION));
	data->green = ft_atoi(colors[1]);
	if (!(data->green <= 255 && data->green >= 0))
		exit(printf(E_CONFIGURATION));
	data->blue = ft_atoi(colors[2]);
	if (!(data->blue <= 255 && data->blue >= 0))
		exit(printf(E_CONFIGURATION));
}

int	add_color(int num, int check[6], t_colors *color, char *options)
{
	int		count;
	char	**colors;

	count = 0;
	color_options(options);
	colors = ft_split(options, ',');
	if (colors == NULL)
		exit(printf(E_MALLOC));
	while (colors[count])
	{
		if (ft_strlen(colors[count]) > 4)
			exit(printf(E_CONFIGURATION));
		count++;
	}
	if (count != 3)
		exit(printf(E_CONFIGURATION));
	adding(color, colors);
	check[num] = 1;
	two_dimensional_mas(&colors);
	return (1);
}

int	add_param(int num, int check[6], char **str, char *path)
{
	if (path == NULL)
		exit(printf(E_CONFIGURATION));
	if (!(path[0] == '.' && path[1] == '/'))
		exit(printf(E_CONFIGURATION));
	if (path[2] == '\n' || path[2] == '\0')
		exit(printf(E_CONFIGURATION));
	*str = ft_substr(path, 0, ft_strlen(path) - 1);
	if (*str == NULL)
		exit(printf(E_MALLOC));
	check[num] = 1;
	return (1);
}

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
	if (!check_end(check))
		exit(printf(E_CONFIGURATION));
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
		if (map[i] == NULL)
			break ;
		i++;
	}
	if (check_map(map) || divided_map(map))
		exit(printf(E_CONFIGURATION));
	map = optimisation_map(map);
	data->map = map;
}
