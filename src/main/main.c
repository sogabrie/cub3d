#include "miniRT.h"

int main()
{
    char *str = "hello minRT";
    printf("%s\n", str);
    ft_putendl_fd("hello miniRT", 1);

    void *mlx = mlx_init();
    void *mlx_win = mlx_new_window(mlx, 500, 500, "minRT");
    mlx_loop(mlx);
    return 0;
}
