#include <math.h>

#include "fdf.h"
#include "minilibx/mlx.h"

void usage(void)
{

}

void	setup_map(t_point **map, unsigned cell)
{
	for (size_t y = 0; y < vec_rows(map); ++y)
	{
		for (size_t x = 0; x < vec_size(map[0]); ++x)
		{
			map[y][x].x = 100 + x * cell;
			map[y][x].y = 10 + y * cell;
		}
	}
}

t_wnd wnd_init(const char *file)
{
	t_wnd wnd;

	wnd.mlxptr = mlx_init();
	wnd.wndptr = mlx_new_window(wnd.mlxptr, W, H, "fdf");
	wnd.imgptr = mlx_new_image(wnd.mlxptr, W, H);
	wnd.img = mlx_get_data_addr(wnd.imgptr, &wnd.bytes,
								&wnd.size_line, &wnd.endian);
	wnd.bytes /= 8;
	wnd.map = get_map(file);
	wnd.map_cp = vec_cp(wnd.map);
	wnd.cell = 10;
	wnd.x_offset = 0;
	wnd.y_offset = 0;
	setup_map(wnd.map, wnd.cell);
	wnd.x_angle = 30.0 * 3.14 / 180;
	return (wnd);
}

void change_map(t_wnd *wnd, int flag)
{
	if (flag == 1)		// x transform
	{
		for (size_t y = 0; y < vec_rows(wnd->map); ++y)
		{
			for (size_t x = 0; x < vec_size(wnd->map[0]); ++x)
			{
				wnd->map_cp[y][x].y = wnd->map[y][x].y * cos(wnd->x_angle) + wnd->map[y][x].z * sin(wnd->x_angle);
				wnd->map_cp[y][x].z = -wnd->map[y][x].y * sin(wnd->x_angle) + wnd->map[y][x].z * cos(wnd->x_angle);
			}
		}
	}

	else if (flag == 2)		// y transform
	{
		for (size_t y = 0; y < vec_rows(wnd->map); ++y)
		{
			for (size_t x = 0; x < vec_size(wnd->map[0]); ++x)
			{
				wnd->map_cp[y][x].x = wnd->map[y][x].x * cos(wnd->y_angle) + wnd->map[y][x].z * sin(wnd->y_angle);
				wnd->map_cp[y][x].z = -wnd->map[y][x].x * sin(wnd->y_angle) + wnd->map[y][x].z * cos(wnd->y_angle);
			}
		}
	}

	else if (flag == 3)
	{
		for (size_t y = 0; y < vec_rows(wnd->map); ++y)
		{
			for (size_t x = 0; x < vec_size(wnd->map[0]); ++x)
			{
				wnd->map_cp[y][x].x = wnd->map[y][x].x * cos(wnd->z_angle) - wnd->map[y][x].y * sin(wnd->z_angle);
				wnd->map_cp[y][x].y = -wnd->map[y][x].x * sin(wnd->z_angle) + wnd->map[y][x].y * cos(wnd->z_angle);
			}
		}
	}
}

void map_print(t_wnd *wnd)
{
	ft_memset(wnd->img, 0, H * wnd->size_line);
	for (size_t y = 0; y < vec_rows(wnd->map_cp); ++y)
	{
		for (size_t x = 0; x < vec_size(wnd->map_cp[0]); ++x)
		{
			if (x != vec_size(wnd->map_cp[0]) - 1)
				draw_line(wnd, &wnd->map_cp[y][x], &wnd->map_cp[y][x + 1], __white);
			if (y != vec_rows(wnd->map_cp) - 1)
				draw_line(wnd, &wnd->map_cp[y][x], &wnd->map_cp[y + 1][x], __white);
		}
	}
	mlx_put_image_to_window(wnd->mlxptr, wnd->wndptr, wnd->imgptr, 0, 0);
}


void map_init(t_wnd *wnd)
{
	for (size_t y = 0; y < vec_rows(wnd->map); ++y)
	{
		for (size_t x = 0; x <= vec_size(wnd->map[0]); ++x)
		{
			wnd->map_cp[y][x].x = wnd->x_offset + (wnd->map[y][x].x - wnd->map[y][x].y) * cos(wnd->x_angle);
			wnd->map_cp[y][x].y = wnd->y_offset + -wnd->map[y][x].z + (wnd->map[y][x].x + wnd->map[y][x].y) * sin(wnd->x_angle);
		}
	}
}



int key_press(int keycode, t_wnd *wnd)
{
	if (keycode == 65307)
		ft_exit(0);
	// printf("%d\n", keycode);
	if (keycode == 97)
		wnd->x_offset -= 10;
	else if (keycode == 100)
		wnd->x_offset += 10;
	else if (keycode == 119)
		wnd->y_offset -= 10;
	else if (keycode == 115)
		wnd->y_offset += 10;
	else if (keycode == 113)
	{
		wnd->cell -= wnd->cell ? 1 : 0;
		setup_map(wnd->map, wnd->cell);
	}
	else if (keycode == 101)
	{
		wnd->cell += 2;
		setup_map(wnd->map, wnd->cell);
	}
	map_init(wnd);
	map_print(wnd);
	return (1);
}

int mouse_press(int button, int x, int y, t_wnd *wnd)
{
	if (wnd && button && x && y)
		return (1);
	return (1);
}

int mouse_release(int button, int x, int y, t_wnd *wnd)
{
	if (wnd && button && x && y)
		return (1);
	return (1);
}

int mouse_move(int x, int y, t_wnd *wnd)
{
	if (x && y && wnd)
		return (1);
	return (1);
}

int main(int argc, const char **argv)
{
	t_wnd	wnd;

	if (argc != 2)
	{
		usage();
		return (0);
	}
	wnd = wnd_init(argv[1]);
	map_init(&wnd);
	map_print(&wnd);


	mlx_hook(wnd.wndptr, 2, 1L << 0, key_press, &wnd);
	mlx_hook(wnd.wndptr, 4, 1L << 2, mouse_press, &wnd);
	mlx_hook(wnd.wndptr, 6, 1L << 13, mouse_move, &wnd);
	mlx_loop(wnd.mlxptr);

	vec_clear(&wnd.map);
	return (0);
}
