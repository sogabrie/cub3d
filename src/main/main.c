#include "miniRT.h"

#define E_ARGC_1 "Error\n! Please specify the .rt file !\n"
#define W_ARGC_2 "! Only the first argument is considered !\n"

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

int	parsing_file(int argc, char *argv)
{
	if (argc == 1 || check_rt(argv, ".rt"))
		return (printf(E_ARGC_1));
	if (argc > 2)
		printf(W_ARGC_2);
	
	return (0);
}

int main(int argc, char *argv[])
{
	if (parsing_file(argc, argv[1]))
		return (1);
}