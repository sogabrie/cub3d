#include "miniRT.h"

// void	permissible_parameters(char *file_name)
// {
// 	int		fd;
// 	char	*str;
// 	int		f_empty;

// 	f_empty = 0;
// 	fd = open_file(file_name);
// 	while (1)
// 	{
// 		str = get_next_line(fd);
// 		if (!str)
// 			break ;
// 		if (str[0] == '\n')
// 		{
// 			free(str);
// 			continue ;
// 		}
// 		//check &f_empty = 1;
// 		free(str);
// 	}
// 	if (!f_empty)
// 		exit(printf(E_FILE_EMPTY));
// }

int	parsing_file(int argc, char *argv)
{
	if (argc == 1 || check_rt(argv, ".rt"))
		return (printf(E_ARGC_1));
	if (argc > 2)
		printf(W_ARGC_2);
	// permissible_parameters(argv);
	return (0);
}

int main(int argc, char *argv[])
{
	if (parsing_file(argc, argv[1]))
		return (1);
}