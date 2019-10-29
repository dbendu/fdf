#include "fdf.h"

void usage(void)
{

}

t_wnd wnd_init(void)
{
	t_wnd wnd;

	wnd.mlxptr = mlx_init();
	wnd.wndptr = mlx_new_window(wnd.mlxptr, W, H, "fdf");
	wnd.imgptr = mlx_new_image(wnd.mlxptr, W, H);
	wnd.img = mlx_get_data_addr(wnd.imgptr, &wnd.bytes_per_pixel, &wnd.size_line, &wnd.endian);
	wnd.bytes_per_pixel /= 8;
	return (wnd);
}

void map_init(t_wnd *wnd)
{
	*(int*)(wnd->img) = __white;
	mlx_put_image_to_window(wnd->mlxptr, wnd->wndptr, wnd->imgptr, 0, 0);
}



int key_press(int keycode, t_wnd *wnd)
{
	static int x = 0;
	static int y = 0;
	if (keycode == 65307)
		exit(0);
	else if (keycode == 119)
		--y;
	else if (keycode == 100)
		++x;
	else if (keycode == 97)
		--x;
	else if (keycode == 115)
		++y;
	mlx_clear_window(wnd->mlxptr, wnd->wndptr);
	mlx_put_image_to_window(wnd->mlxptr, wnd->wndptr, wnd->imgptr, x, y);
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
	wnd.map = get_map(argv[1]);
	wnd = wnd_init();

	map_init(&wnd);



	mlx_hook(wnd.wndptr, 2, 1L << 0, key_press, &wnd);
	mlx_hook(wnd.wndptr, 4, 1L << 2, mouse_press, &wnd);
	mlx_hook(wnd.wndptr, 6, 1L << 13, mouse_move, &wnd);
	mlx_loop(wnd.mlxptr);

	vec_clear(&wnd.map);

	return (0);
}
