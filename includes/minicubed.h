#ifndef MINICUBED_H
#define MINICUBED_H

#include "mlx.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#define WIDTH 1280
#define HEIGHT 720

#define W 119
#define A 97
#define S 115
#define D 100

#define PI 3.1415
typedef struct s_player
{
        float x;
        float y;

        bool key_up;
        bool key_down;
        bool key_left;
        bool key_right;
} t_player;

typedef struct s_cubed
{
        void *mlx;
        void *win;
        void *img;
        char *data;
        int bpp;
        int size_line;
        int endian;
        t_player player;
        char **map;
} t_cubed;

void init_player(t_player *player);
int key_press(int keycode, t_player *player);
int key_release(int keycode, t_player *player);
void move_player(t_player *player);

#endif