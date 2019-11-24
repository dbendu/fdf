#include <math.h>

#include "fdf.h"

void usage(void)
{
	printf("One file: ./fdf map\n");
	ft_exit(0);
}

void maps_setup(t_wnd *wnd)
{
	for (size_t y = 0; y < vec_rows(wnd->map); ++y)
	{
		for (size_t x = 0; x < vec_size(wnd->map[0]); ++x)
		{
			wnd->map[y][x].x = wnd->cell + wnd->x_offset + x * wnd->cell;
			wnd->map[y][x].y = wnd->cell + wnd->y_offset + y * wnd->cell;
			wnd->map_cp[y][x].x = wnd->map[y][x].x;
			wnd->map_cp[y][x].y = wnd->map[y][x].y;
		}
	}
}

void print_map(t_wnd *wnd)
{
	ft_memset(wnd->img, 0, wnd->size_line * HEIGHT);
	for (size_t y = 0; y < vec_rows(wnd->map_cp); ++y)
	{
		for (size_t x = 0; x < vec_size(wnd->map_cp[0]); ++x)
		{
			if (x != vec_size(wnd->map_cp[0]) - 1)
				draw_line(wnd, &wnd->map_cp[y][x], &wnd->map_cp[y][x + 1], wnd->map[y][x].z || wnd->map[y][x + 1].z ? __purple : __white);
			if (y != vec_rows(wnd->map_cp) - 1)
				draw_line(wnd, &wnd->map_cp[y][x], &wnd->map_cp[y + 1][x], wnd->map[y][x].z || wnd->map[y + 1][x].z ? __purple :  __white);
		}
	}
	mlx_put_image_to_window(wnd->mlxptr, wnd->wndptr, wnd->imgptr, 0, 0);
}

void change_angle(t_wnd *wnd, int flag)
{
	if (flag == 1)		// x transform
	{
		for (size_t y = 0; y < vec_rows(wnd->map); ++y)
		{
			for (size_t x = 0; x < vec_size(wnd->map[0]); ++x)
			{
				wnd->map[y][x].x -= wnd->x_center;
				wnd->map[y][x].y -= wnd->y_center;
				wnd->map_cp[y][x].y = wnd->map[y][x].y * cos(wnd->x_angle) + wnd->map[y][x].z * sin(wnd->x_angle);
				wnd->map_cp[y][x].z = -wnd->map[y][x].y * sin(wnd->x_angle) + wnd->map[y][x].z * cos(wnd->x_angle);
				wnd->map[y][x].x += wnd->x_center;
				wnd->map[y][x].y += wnd->y_center;
				wnd->map_cp[y][x].y += wnd->y_center;
			}
		}
	}

	else if (flag == 2)		// y transform
	{
		for (size_t y = 0; y < vec_rows(wnd->map); ++y)
		{
			for (size_t x = 0; x < vec_size(wnd->map[0]); ++x)
			{
				wnd->map[y][x].x -= wnd->x_center;
				wnd->map[y][x].y -= wnd->y_center;
				wnd->map_cp[y][x].x = wnd->map[y][x].x * cos(wnd->y_angle) + wnd->map[y][x].z * sin(wnd->y_angle);
				wnd->map_cp[y][x].z = -wnd->map[y][x].x * sin(wnd->y_angle) + wnd->map[y][x].z * cos(wnd->y_angle);
				wnd->map[y][x].x += wnd->x_center;
				wnd->map[y][x].y += wnd->y_center;
				wnd->map_cp[y][x].x += wnd->x_center;
			}
		}
	}

	else if (flag == 3)
	{
		for (size_t y = 0; y < vec_rows(wnd->map); ++y)
		{
			for (size_t x = 0; x < vec_size(wnd->map[0]); ++x)
			{
				wnd->map[y][x].x -= wnd->x_center;
				wnd->map[y][x].y -= wnd->y_center;
				wnd->map_cp[y][x].x = wnd->map[y][x].x * cos(wnd->z_angle) - wnd->map[y][x].y * sin(wnd->z_angle);
				wnd->map_cp[y][x].y = -wnd->map[y][x].x * sin(wnd->z_angle) + wnd->map[y][x].y * cos(wnd->z_angle);
				wnd->map_cp[y][x].x += wnd->x_center;
				wnd->map_cp[y][x].y += wnd->y_center;
				wnd->map[y][x].x += wnd->x_center;
				wnd->map[y][x].y += wnd->y_center;
			}
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
	wnd.x_offset = 0;
	wnd.y_offset = 0;
	wnd.cell = 10;
	wnd.map = get_map(argv[1]);
	wnd.map_cp = vec_cp(wnd.map);
	wnd.x_center = (wnd.cell + vec_size(wnd.map[0]) * wnd.cell) / 2;
	wnd.y_center = (wnd.cell + vec_rows(wnd.map) * wnd.cell) / 2;
	maps_setup(&wnd);
	return (wnd);
}

int key_press(int keycode, t_wnd *wnd)
{
	printf("%d\n", keycode);
	if (keycode == ESC)
		ft_exit(0);
	else if (keycode == MINUS)
	{
		--wnd->cell;
		maps_setup(wnd);
	}
	else if (keycode == PLUS)
	{
		++wnd->cell;
		maps_setup(wnd);
	}
	else if (keycode == UP)
	{
		wnd->y_center -= 10;
		wnd->y_offset -= 10;
		maps_setup(wnd);
	}
	else if (keycode == DOWN)
	{
		wnd->y_center += 10;
		wnd->y_offset += 10;
		maps_setup(wnd);
	}
	else if (keycode == LEFT)
	{
		wnd->x_center -= 10;
		wnd->x_offset -= 10;
		maps_setup(wnd);
	}
	else if (keycode == RIGHT)
	{
		wnd->x_center += 10;
		wnd->x_offset += 10;
		maps_setup(wnd);
	}
	else if (keycode == W)
	{
		wnd->x_angle -= 3.14 / 360 * 3;
		change_angle(wnd, 1);
	}
	else if (keycode == S)
	{
		wnd->x_angle += 3.14 / 360 * 3;
		change_angle(wnd, 1);
	}
	else if (keycode == A)
	{
		wnd->y_angle -= 3.14 / 360 * 3;
		change_angle(wnd, 2);
	}
	else if (keycode == D)
	{
		wnd->y_angle += 3.14 / 360 * 3;
		change_angle(wnd, 2);
	}
	else if (keycode == 32)
	{
		wnd->x_angle = 0;
		wnd->y_angle = 0;
		change_angle(wnd, 1);
		change_angle(wnd, 2);
	}
	else if (keycode == Q)
	{
		wnd->z_angle -= 3.14 / 360 * 3;
		change_angle(wnd, 3);
	}
	else if (keycode == E)
	{
		wnd->z_angle += 3.14 / 360 * 3;
		change_angle(wnd, 3);
	}
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
	mlx_put_image_to_window(wnd.mlxptr, wnd.wndptr, wnd.imgptr, 0, 0);
	mlx_hook(wnd.wndptr, 2, 1L << 0, key_press, &wnd);
	mlx_loop(wnd.mlxptr);





	return (0);
}
