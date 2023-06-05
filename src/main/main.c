#include "cub3D.h"

int	main(int argc, char *argv[])
{
	t_data_segment	*data;

	data = (t_data_segment *)malloc(sizeof(t_data_segment));
	if (data == NULL)
		exit(printf(E_MALLOC));
	if (pars_part(argc, argv[1], &data))
		return (1);
	// system("leaks cub3D");
	// printf("data.options.north_texture = %s\n", data->options.north_texture);
	// printf("data.options.south_texture = %s\n", data->options.south_texture);
	// printf("data.options.west_texture = %s\n", data->options.west_texture);
	// printf("data.options.east_texture = %s\n", data->options.east_texture);
	// printf("floor : %d %d %d\n", data->options.floor.red, data->options.floor.green, data->options.floor.blue);
	// printf("ceiling : %d %d %d\n", data->options.ceiling.red, data->options.ceiling.green, data->options.ceiling.blue);
	// for(int i = 0; data->map[i]; i++)
	// 	printf("%s", data->map[i]);
	// printf("\n");
	// printf("x_axis %d\n", data->x_axis);
	// printf("y_axis %d\n", data->y_axis);
	return (0);
}
