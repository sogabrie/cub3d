#include "cub3D.h"

int	pars_map(char **map, int i, int j)
{
	int	count;
	int	c_count;

	c_count = 0;
	count = y_counts(map);
	if (first_last_y(map[0]) || first_last_y(map[count - 1]))
		return (1);
	while (++i < count - 1)
	{
		if (c_count > 1)
			return (1);
		while (map[i][++j])
		{
			if (ft_strchr("NSEW	", map[i][j]))
				c_count++;
			if (!ft_strchr("10 NSEWD\n", map[i][j]))
				return (1);
			if (ft_strchr("0NSEWD", map[i][j]) && check_walls(map, i, j))
				return (1);
		}
		j = -1;
	}
	if (c_count == 0)
		return (1);
	return (0);
}

int	check_walls(char **map, int i, int j)
{
	if (j == 0 || (j > ft_strlen(map[i + 1]) || j > ft_strlen(map[i - 1])))
		return (1);
	if (ft_strchr(" \n\0", map[i + 1][j]) || ft_strchr(" \n\0", map[i + 1][j + 1])
		|| ft_strchr(" \n\0", map[i + 1][j - 1]))
		return (1);
	if (ft_strchr(" \n\0", map[i - 1][j]) || ft_strchr(" \n\0", map[i - 1][j + 1])
		|| ft_strchr(" \n\0", map[i + 1][j - 1]))
		return (1);
	if (ft_strchr(" \n\0", map[i][j + 1]))
		return (1);
	if (ft_strchr(" \n\0", map[i][j - 1]))
		return (1);
	return (0);
}

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

int	max_x_axis(char **map)
{
	int	max;
	int	i;
	int	rep_max;

	i = 0;
	max = ft_strlen(map[0]);
	while (map[++i])
	{
		rep_max = ft_strlen(map[i]);
		if (rep_max > max)
			max = rep_max;
	}
	return (max);
}
