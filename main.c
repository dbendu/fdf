#include <math.h>
#include <unistd.h>
#include <pthread.h>

#include "fdf.h"

// void usage(void)
// {
// 	printf("One file: ./fdf map\n");
// 	ft_exit(0);
// }

void print_map(t_wnd *wnd)
{
	ft_memset(wnd->img, 0, wnd->size_line * HEIGHT);
	for (size_t y = 0; y < vec_rows(wnd->map_cp); ++y)
	{
		for (size_t x = 0; x < vec_size(wnd->map_cp[0]); ++x)
		{
			wnd->map_cp[y][x].a_color = wnd->map[y][x].a_color;
			wnd->map_cp[y][x].g_color = wnd->map[y][x].g_color;
			wnd->map_cp[y][x].b_color = wnd->map[y][x].b_color;
			if (x != vec_size(wnd->map_cp[0]) - 1)
			{
				wnd->map_cp[y][x + 1].a_color = wnd->map[y][x + 1].a_color;
				wnd->map_cp[y][x + 1].g_color = wnd->map[y][x + 1].g_color;
				wnd->map_cp[y][x + 1].b_color = wnd->map[y][x + 1].b_color;
				draw_line(wnd, &wnd->map_cp[y][x], &wnd->map_cp[y][x + 1]);
			}
			if (y != vec_rows(wnd->map_cp) - 1)
			{
				wnd->map_cp[y + 1][x].a_color = wnd->map_cp[y + 1][x].a_color;
				wnd->map_cp[y + 1][x].g_color = wnd->map_cp[y + 1][x].g_color;
				wnd->map_cp[y + 1][x].b_color = wnd->map_cp[y + 1][x].b_color;
				draw_line(wnd, &wnd->map_cp[y][x], &wnd->map_cp[y + 1][x]);
			}
		}
	}
	mlx_put_image_to_window(wnd->mlxptr, wnd->wndptr, wnd->imgptr, 0, 0);
}

void change_angle(t_wnd *wnd)
{
	double sin_x = sin(wnd->x_angle);
	double sin_y = sin(wnd->y_angle);
	double sin_z = sin(wnd->z_angle);
	double cos_x = cos(wnd->x_angle);
	double cos_z = cos(wnd->z_angle);
	double cos_y = cos(wnd->y_angle);
		for (size_t y = 0; y < vec_rows(wnd->map); ++y)
		{
			for (size_t x = 0; x < vec_size(wnd->map[0]); ++x)
			{
				wnd->map_cp[y][x].x = x * wnd->cell;
				wnd->map_cp[y][x].y = y * wnd->cell;
				int x_ = wnd->map_cp[y][x].x;
				int y_ = wnd->map_cp[y][x].y;
				int z_ = wnd->map[y][x].z;
				if (z_ && z_ > 0)
					z_ += wnd->z_shift;
				else if (z_ && z_ < 0)
					z_ -= wnd->z_shift;
				wnd->map_cp[y][x].y = y_ * cos_x + z_ * sin_x;
				wnd->map_cp[y][x].z = -y_ * sin_x + z_ * cos_x;

				x_ = wnd->map_cp[y][x].x;
				y_ = wnd->map_cp[y][x].y;
				z_ = wnd->map_cp[y][x].z;
				wnd->map_cp[y][x].x = x_ * cos_y + z_ * sin_y;
				wnd->map_cp[y][x].z = -x_ * sin_y + z_ * cos_y;

				x_ = wnd->map_cp[y][x].x;
				y_ = wnd->map_cp[y][x].y;
				z_ = wnd->map_cp[y][x].z;
				wnd->map_cp[y][x].x = x_ * cos_z - y_ * sin_z;
				wnd->map_cp[y][x].y = x_ * sin_z + y_ * cos_z;


				wnd->map_cp[y][x].x += wnd->x_offset;
				wnd->map_cp[y][x].y += wnd->y_offset;
			}
		}
}

t_wnd wnd_init(const char **argv)
{
	t_wnd wnd;

	wnd.mlxptr = mlx_init();
	wnd.wndptr = mlx_new_window(wnd.mlxptr, WIDTH, HEIGHT, "fdf");
	wnd.imgptr = mlx_new_image(wnd.mlxptr, WIDTH, HEIGHT);
	wnd.img = mlx_get_data_addr(wnd.imgptr, &wnd.bytes, &wnd.size_line, &wnd.endian);
	wnd.bytes /= 8;
	wnd.x_angle = 0;
	wnd.y_angle = 0;
	wnd.z_angle = 0;
	wnd.x_offset = 300;
	wnd.y_offset = 300;
	wnd.cell = 1;
	wnd.z_shift = 0;
	wnd.map = get_map(argv[1]);
	wnd.map_cp = vec_cp(wnd.map);
	// for (size_t y = 0; y < vec_rows(wnd.map); ++y)
	// {
	// 	for (size_t x = 0; x < vec_size(wnd.map[0]); ++x)
	// 		printf("%8d\t", wnd.map[y][x].color);
	// 	printf("\n");
	// }
	wnd.x_center = (wnd.cell + vec_size(wnd.map[0]) * wnd.cell) / 2;
	wnd.y_center = (wnd.cell + vec_rows(wnd.map) * wnd.cell) / 2;
	change_angle(&wnd);
	print_map(&wnd);
	return (wnd);
}

void shift_map(t_wnd *wnd, int x_, int y_)
{
	size_t y;
	size_t x;
	size_t rows;
	size_t cols;

	wnd->x_offset += x_;
	wnd->y_offset += y_;

	rows = vec_rows(wnd->map);
	cols = vec_size(wnd->map[0]);
	y = 0;
	while (y < rows)
	{
		x = 0;
		while (x < cols)
		{
			wnd->map[y][x].x += x_;
			wnd->map[y][x].y += y_;
			wnd->map_cp[y][x].x += x_;
			wnd->map_cp[y][x].y += y_;
			++x;
		}
		++y;
	}
}

int key_press(int keycode, t_wnd *wnd)
{
	// printf("%d\n", keycode);
	if (keycode == ESC)
		ft_exit(0);
	else if (keycode == MINUS)
		--wnd->cell;
	else if (keycode == PLUS)
		++wnd->cell;
	else if (keycode == UP)
		shift_map(wnd, 0, -50);
	else if (keycode == DOWN)
		shift_map(wnd, 0, 50);
	else if (keycode == LEFT)
		shift_map(wnd, -50, 0);
	else if (keycode == RIGHT)
		shift_map(wnd, 50, 0);
	else if (keycode == W)
		wnd->x_angle -= 3.14 / 360 * 6;
	else if (keycode == S)
		wnd->x_angle += 3.14 / 360 * 6;
	else if (keycode == A)
		wnd->y_angle -= 3.14 / 360 * 6;
	else if (keycode == D)
		wnd->y_angle += 3.14 / 360 * 6;
	else if (keycode == Q)
		wnd->z_angle -= 3.14 / 360 * 6;
	else if (keycode == E)
		wnd->z_angle += 3.14 / 360 * 6;
	else if (keycode == I)
		wnd->z_shift -= 10;
	else if (keycode == O)
		wnd->z_shift += 10;
	else if (keycode == SPACE)
	{
		wnd->x_angle = 0;
		wnd->y_angle = 0;
		wnd->z_angle = 0;
		wnd->x_offset = 0;
		wnd->y_offset = 0;
		wnd->z_shift = 0;
	}
	if (keycode != UP && keycode != DOWN && keycode != LEFT && keycode != RIGHT)
		change_angle(wnd);
	// printf("%f\n", wnd->x_angle);
	print_map(wnd);
	return (1);
}

int main(int argc, const char **argv)
{
	t_wnd wnd;

	if (argc != 2)
	{
		// usage();
		return (0);
	}

	wnd = wnd_init(argv);
	mlx_put_image_to_window(wnd.mlxptr, wnd.wndptr, wnd.imgptr, 0, 0);
	mlx_hook(wnd.wndptr, 2, 1L << 0, key_press, &wnd);
	mlx_loop(wnd.mlxptr);





	return (0);
}
