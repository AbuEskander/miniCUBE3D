#include "minicubed.h"

void put_pixel(int x, int y, int color, t_cubed *cubed)
{
        if (x >= WIDTH || y >= HEIGHT || x < 0 || y < 0)
                return;
        int index = y * cubed->size_line + x * cubed->bpp / 8;
        cubed->data[index] = color & 0xFF;
        cubed->data[index + 1] = (color >> 8) & 0xFF;
        cubed->data[index + 2] = (color >> 16) & 0xFF;
}
void draw_square(int x, int y, int size, int color, t_cubed *cubed)
{
        for (int i = 0; i < size; i++)
                put_pixel(x + i, y, color, cubed);
        for (int i = 0; i < size; i++)
                put_pixel(x, y + i, color, cubed);
        for (int i = 0; i < size; i++)
                put_pixel(x + size, y + i, color, cubed);
        for (int i = 0; i < size; i++)
                put_pixel(x + i, y + size, color, cubed);
}
void draw_map(t_cubed *cubed)
{
        char **map = cubed->map;
        int color = 0x0000FF;
        for (size_t y = 0; map[y]; y++)
                for (size_t x = 0; map[y][x]; x++)
                        if (map[y][x] == '1')
                                draw_square(x * 64, y * 64, 64, color, cubed);
}

void clear_image(t_cubed *cubed)
{
        for (size_t i = 0; i < HEIGHT; i++)
                for (size_t j = 0; j < WIDTH; j++)
                        put_pixel(j, i, 0, cubed);
}
char **get_map()
{
        char **map = malloc(sizeof(char *) * 11);
        map[0] = "1111111111111111111";
        map[1] = "1000000000000000001";
        map[2] = "1000000000000000001";
        map[3] = "1000000000000000001";
        map[4] = "1000000000000000001";
        map[5] = "1000000000000000001";
        map[6] = "1000000000000000001";
        map[7] = "1000000000000000001";
        map[8] = "1000000000000000001";
        map[9] = "1111111111111111111";
        map[10] = NULL;
        return (map);
}
void init_cubed(t_cubed *cubed)
{
        init_player(&cubed->player);
        cubed->map = get_map();
        cubed->mlx = mlx_init();
        cubed->win = mlx_new_window(cubed->mlx, WIDTH, HEIGHT, "MINICUBED");
        cubed->img = mlx_new_image(cubed->mlx, WIDTH, HEIGHT);
        cubed->data = mlx_get_data_addr(cubed->img, &cubed->bpp, &cubed->size_line, &cubed->endian);
        mlx_put_image_to_window(cubed->mlx, cubed->win, cubed->img, 0, 0);
}
int draw_loop(t_cubed *cubed)
{
        t_player *player = &cubed->player;
        move_player(player);
        clear_image(cubed);
        draw_square(player->x, player->y, 20, 0xAA00AA, cubed);
        draw_map(cubed);
        mlx_put_image_to_window(cubed->mlx, cubed->win, cubed->img, 0, 0);
        return (1);
}
int main()
{
        t_cubed cubed;

        init_cubed(&cubed);
        mlx_hook(cubed.win, 2, 1L << 0, key_press, &cubed.player);
        mlx_hook(cubed.win, 3, 1L << 1, key_release, &cubed.player);

        mlx_loop_hook(cubed.mlx, draw_loop, &cubed);
        mlx_loop(cubed.mlx);
}