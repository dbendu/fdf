#include "fdf.h"
#include "minilibx/mlx.h"

void usage(void)
{

}


void __exit(t_wnd *wnd)
{
	vec_clear(&wnd->map);
	exit(0);
}

t_wnd wnd_init(const char *file)
{
	t_wnd wnd;

	wnd.mlxptr = mlx_init();
	wnd.wndptr = mlx_new_window(wnd.mlxptr, W, H, "fdf");
	wnd.imgptr = mlx_new_image(wnd.mlxptr, W, H);
	wnd.img = mlx_get_data_addr(wnd.imgptr, &wnd.bytes_per_pixel,
								&wnd.size_line, &wnd.endian);
	wnd.bytes_per_pixel /= 8;
	wnd.map = get_map(file);
	return (wnd);
}


void map_init(t_wnd *wnd)
{
	t_point from;
	t_point to;
	from.x = 50;
	to.x = 50 + vec_size(wnd->map[0]) * 50;
	from.y = 50;
	for (size_t i = 0; i <= vec_rows(wnd->map); ++i)
	{
		to.y = from.y;
		draw_line(wnd, &from, &to);
		from.y += 50;
	}

	from.y = 50;
	to.y = 50 + vec_rows(wnd->map) * 50;
	from.x = 50;
	for (size_t i = 0; i <= vec_size(wnd->map[0]); ++i)
	{
		to.x = from.x;
		draw_line(wnd, &to, &from);
		from.x += 50;
	}

	for (size_t i = 0; i < vec_rows(wnd->map); ++i)
	{
		for (size_t j = 0; j < vec_size(wnd->map[0]); ++j)
		{
			if (wnd->map[i][j].z)
			{
				from.y = 50 + i * 50;
				to.y = from.y + 50;
				from.x = 50 + j * 50;
				to.x = from.x + 50;
				draw_line(wnd, &from, &to);

				from.y += 50;
				to.y -= 50;
				draw_line(wnd, &from, &to);
			}
		}
	}

	mlx_put_image_to_window(wnd->mlxptr, wnd->wndptr, wnd->imgptr, 0, 0);
}



int key_press(int keycode, t_wnd *wnd)
{
	if (keycode == 65307)
		__exit(wnd);

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


	mlx_hook(wnd.wndptr, 2, 1L << 0, key_press, &wnd);
	mlx_hook(wnd.wndptr, 4, 1L << 2, mouse_press, &wnd);
	mlx_hook(wnd.wndptr, 6, 1L << 13, mouse_move, &wnd);
	mlx_loop(wnd.mlxptr);

	vec_clear(&wnd.map);
	return (0);
}
