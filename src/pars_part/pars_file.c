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
		if (options[i] == ',')
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

void	param_check(t_data_segment *data, char *str, int check[6])
{
	char	**tmp;
	int		status;

	tmp = ft_split(str, ' ');
	if (tmp == NULL || tmp[0] == NULL)
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
}
