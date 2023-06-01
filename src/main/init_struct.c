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
	if (path[2] == '\n' || path[2] == '\0')
		exit(printf(E_CONFIGURATION));
	*str = ft_strdup(path);
	if (*str == NULL)
		exit(printf(E_MALLOC));
	check[num] = 1;
	return (1);
}
