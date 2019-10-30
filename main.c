#include "fdf.h"
#include "minilibx/mlx.h"

#define W	700
#define H	500

void usage(void)
{

}


typedef struct	s_wnd
{
	void	*mlx;
	void	*wnd;
	void	*img;
	char	*data;
	t_point	**map;

	int		bytes_per_pixel;
	int		size_line;
	int		endian;
}				t_wnd;


void map_init(t_wnd *wnd)
{
	*(int*)(wnd->data + 100 * wnd->size_line + 200) = __white;
	mlx_put_image_to_window(wnd->mlx, wnd->wnd, wnd->img, 0, 0);
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
	mlx_put_image_to_window(wnd->mlx, wnd->wnd, wnd->img, x, y);
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
	wnd.mlx = mlx_init();
	wnd.wnd = mlx_new_window(wnd.mlx, W, H, "fdf");
	wnd.img = mlx_new_image(wnd.mlx, W, H);
	wnd.data = mlx_get_data_addr(wnd.img, &wnd.bytes_per_pixel, &wnd.size_line, &wnd.endian);
	wnd.bytes_per_pixel /= 8;

	map_init(&wnd);


	mlx_hook(wnd.wnd, 2, 1L << 0, key_press, &wnd);
	mlx_hook(wnd.wnd, 4, 1L << 2, mouse_press, &wnd);
	mlx_hook(wnd.wnd, 6, 1L << 13, mouse_move, &wnd);
	mlx_loop(wnd.mlx);

	vec_clear(&wnd.map);
	return (0);
}
