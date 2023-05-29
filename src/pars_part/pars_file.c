#include "miniRT.h"

int	open_file(char *file_name)
{
	int	fd;

	fd = open(file_name, O_RDONLY);
	if (fd < 0)
		exit(printf(E_OPEN_FILE));
	return (fd);
}

int	check_rt(char *arg, char *rt)
{
	size_t	len_arg;
	size_t	len_rt;

	len_arg = ft_strlen(arg);
	len_rt = ft_strlen(rt);
	if (len_arg == len_rt)
		return (1);
	while (len_rt > 0)
	{
		--len_arg;
		--len_rt;
		if (arg[len_arg] != rt[len_rt])
			return (1);
	}
	return (0);
}
