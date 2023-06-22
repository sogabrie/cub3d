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

int	check_map(char **map)
{
	int	i;

	i = -1;
	if (map == NULL || map[0] == NULL)
		return (1);
	while (map[++i])
	{
		if (map[i][0] == '\n')
			continue ;
		if (!unprinted(map[i]))
			return (0);
	}
	return (1);
}
