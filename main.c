#include <stdio.h>

#include "fdf.h"

void out(t_wnd *wnd)
{
	mlx_destroy_image(wnd->mlxptr, wnd->imgptr);
	mlx_destroy_window(wnd->mlxptr, wnd->wndptr);
	ft_free_all();
	exit(0);
}

void usage(void)
{
	write(1, "One file: ./fdf file\n", 21);
}

t_wnd wnd_init(const char **argv)
{
	t_wnd wnd;

	wnd.mlxptr = mlx_init();
	wnd.wndptr = mlx_new_window(wnd.mlxptr, WIDTH, HEIGHT, "fdf");
	wnd.imgptr = mlx_new_image(wnd.mlxptr, WIDTH, HEIGHT);
	wnd.img = mlx_get_data_addr(wnd.imgptr, &wnd.bytes, &wnd.size_line, &wnd.endian);
	wnd.bytes /= 8;
	wnd.map = get_map(argv[1]);
	wnd.map[0][0].y = 1;
	wnd.x_angle = 0;
	wnd.y_angle = 0;
	wnd.z_angle = 0;
	wnd.x_offset = 0;
	wnd.y_offset = 0;
	wnd.z_offset = 0;
	wnd.cell = 50;
	return (wnd);
}

void print_map(t_wnd *wnd)
{
	for (size_t y = 0; y < vec_rows(wnd->map); ++y)
	{
		for (size_t x = 0; x < vec_size(wnd->map[0]); ++x)
		{
			wnd->map[y][x].x = wnd->x_offset + wnd->cell + x * wnd->cell;
			wnd->map[y][x].y = wnd->y_offset + wnd->cell + y * wnd->cell;
		}
	}
	printf("%f\t%d\n", wnd->map[0][0].y, wnd->y_offset);
	ft_memset(wnd->img, 0, wnd->size_line * HEIGHT);
	for (size_t y = 0; y < vec_rows(wnd->map); ++y)
	{
		for (size_t x = 0; x < vec_size(wnd->map[0]); ++x)
		{
			if (x != vec_size(wnd->map[0]) - 1)
				draw_line(wnd, &wnd->map[y][x], &wnd->map[y][x + 1], wnd->map[y][x].z || wnd->map[y][x + 1].z ? __purple : __white);
			if (y != vec_rows(wnd->map) - 1)
				draw_line(wnd, &wnd->map[y][x], &wnd->map[y + 1][x], wnd->map[y][x].z || wnd->map[y + 1][x].z ? __purple : __white);
		}
	}
	mlx_put_image_to_window(wnd->mlxptr, wnd->wndptr, wnd->imgptr, 0, 0);
}

int key_press(int key, t_wnd *wnd)
{
	if (key == ESC)
		out(wnd);
	// printf("%d\n", key);
	if (key == RIGHT)
		wnd->x_offset += 10;
	else if (key == LEFT)
		wnd->x_offset -= 10;
	else if (key == UP)
		wnd->y_offset -= 10;
	else if (key == DOWN)
		wnd->y_offset += 10;
	else if (key == MINUS && wnd->cell > 4)
		wnd->cell -= 5;
	else if (key == PLUS)
		wnd->cell += 5;
	else if (key == SPACE)
	{
		wnd->x_offset = 0;
		wnd->y_offset = 0;
		wnd->cell = 50;
	}
	else if (key == W)
		wnd->x_angle -= 3.14 / 180 * 5;
	else if (key == S)
		wnd->x_angle += 3.14 / 180 * 5;
	else if (key == A)
		wnd->y_angle -= 3.14 / 180 * 5;
	else if (key == D)
		wnd->y_angle += 3.14 / 180 * 5;
	else if (key == Q)
		wnd->z_angle -= 3.14 / 180 * 5;
	else if (key == E)
		wnd->z_angle += 3.14 / 180 * 5;

	print_map(wnd);
	return (1);
}

int main(int argc, const char **argv)
{
	t_wnd wnd;

	if (argc != 2)
	{
		usage();
		return (0);
	}
	wnd = wnd_init(argv);
	mlx_hook(wnd.wndptr, 2, 1L << 0, key_press, &wnd);

	mlx_loop(wnd.mlxptr);
	return (0);
}
