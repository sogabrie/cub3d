#include "miniRT.h"

char	**creat_mas_rt(char **file_rt, char *file_name)
{
	int		fd;
	char	*tmp_str;
	char	*tmp;

	fd = open_file(file_name);
	tmp_str = NULL;
	while (1)
	{
		tmp = get_next_line(fd);
		if (tmp == NULL)
			break ;
		tmp_str = ft_strjoin_exlusive(tmp_str, tmp);
		if (tmp_str == NULL)
			exit(printf(E_MALLOC));
		free(tmp);
	}
	close(fd);
	if (tmp_str == NULL)
		exit(printf(E_FILE_EMPTY));
	file_rt = ft_split(tmp_str, '\n');
	if (file_rt == NULL)
		exit(printf(E_MALLOC));
	free(tmp_str);
	return (file_rt);
}

int	parsing_file(int argc, char *argv)
{
	char	**file_rt;

	file_rt = NULL;
	if (argc == 1 || check_rt(argv, ".rt"))
		return (printf(E_ARGC_1));
	if (argc > 2)
		printf(W_ARGC_2);
	file_rt = creat_mas_rt(file_rt, argv);
	for(int i = 0; file_rt[i]; i++)
		printf("%s\n", file_rt[i]);
	return (0);
}

int main(int argc, char *argv[])
{
	if (parsing_file(argc, argv[1]))
		return (1);
}