#include "cub3D.h"

typedef struct s_colors {
	int	red;
	int	green;
	int	blue;
}	t_colors;

typedef struct s_options {
	char		*north_texture;
	char		*south_texture;
	char		*west_texture;
	char		*east_texture;
	t_colors	floor;
	t_colors	ceiling;

}	t_options;

typedef struct s_data_segment {
	char		**map;
	t_options	options;
	// ..
	// ..
	// ..
}	t_data_segment;

void	two_dimensional_mas(char ***str)
{
	size_t	i;

	i = 0;
	if (*str != NULL)
	{
		while ((*str)[i])
		{
			free((*str)[i]);
			i++;
		}
		free(*str);
		*str = NULL;
	}
}

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

int add_color(int num, int check[6], t_colors *color, char *options)
{
	int		i;
	char	**colors;

	i = -1;
	if (options == NULL)
		exit(printf(E_CONFIGURATION));
	while(options[++i])
	{
		if (options[i] == ',')
			continue ;
		if (!ft_isdigit(options[i]) && options[i + 1] != '\0')
			exit(printf(E_CONFIGURATION));
	}
	int count = 0;
	colors = ft_split(options, ',');
	if (colors == NULL)
		exit(printf(E_CONFIGURATION));
	while(colors[count])
		count++;
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
	*str = ft_strdup(path);
	if (*str == NULL)
		exit(printf(E_MALLOC));
	check[num] = 1;
	return (1);
}

void	param_check(t_data_segment *data, char *str, int check[6])
{
	char	**tmp;
	int		status;

	tmp = ft_split(str, ' ');
	if (tmp == NULL)
		exit(printf(E_MALLOC));
	status = 0;
	if (ft_strcmp(tmp[0], "NO") == 0 && check[0] != 1)
		status = add_param(0, check, &(data->options.north_texture), tmp[1]);
	if (ft_strcmp(tmp[0], "SO") == 0 && check[1] != 1)
		status = add_param(1, check, &(data->options.south_texture), tmp[1]);
	if (ft_strcmp(tmp[0], "WE") == 0 && check[2] != 1)
		status = add_param(2, check, &(data->options.west_texture), tmp[1]);
	if (ft_strcmp(tmp[0], "EA") == 0 && check[3] != 1)
		status = add_param(3, check, &(data->options.east_texture), tmp[1]);
	if (ft_strchr(tmp[0], 'F'))
		status = add_color(4, check, &(data->options.floor), tmp[1]);
	if (ft_strchr(tmp[0], 'C'))
		status = add_color(5, check, &(data->options.ceiling), tmp[1]);
	if (status != 1)
	{
		two_dimensional_mas(&tmp);
		exit(printf(E_CONFIGURATION));
	}
	two_dimensional_mas(&tmp);
				system("leaks cub3D");
}

int	check_end(int check[6])
{
	int i;

	i = 0;
	while(i < 6)
	{
		if (check[i] == 0)
			return (0);
		i++;
	}
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
		param_check(data, tmp, check);
		free(tmp);
	}
	if (!check_end(check))
		exit(printf(E_CONFIGURATION));
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

	if (pars_part(argc, argv[1], &data))
		return (1);
	// system("leaks cub3D");
	printf("data.options.north_texture = %s", data->options.north_texture);
	printf("data.options.south_texture = %s", data->options.south_texture);
	printf("data.options.west_texture = %s", data->options.west_texture);
	printf("data.options.east_texture = %s", data->options.east_texture);
	printf("floor : %d %d %d\n", data->options.floor.red, data->options.floor.green, data->options.floor.blue);
	printf("ceiling : %d %d %d\n", data->options.ceiling.red, data->options.ceiling.green, data->options.ceiling.blue);
	return 0;
}
