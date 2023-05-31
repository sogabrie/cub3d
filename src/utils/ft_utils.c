#include "cub3D.h"

int	check_end(int check[6])
{
	int	i;

	i = 0;
	while (i < 6)
	{
		if (check[i] == 0)
			return (0);
		i++;
	}
	return (1);
}
