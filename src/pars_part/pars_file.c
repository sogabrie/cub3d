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
