#include <math.h>
#include <unistd.h>
#include <stdio.h>
#include <pthread.h>

#include "fdf.h"

void usage(void)
{
	printf("One file: ./fdf map\n");
	ft_exit(0);
}

void *change1(void *param)
{
	t_wnd *wnd = (t_wnd*)param;
	int x_;
	int y_;
	int z_;

	for (size_t y = 0; y < wnd->rows / 4; ++y)
		for (size_t x = 0; x < wnd->cols; ++x)
		{
			wnd->map_cp[y][x].x = x * wnd->cell;
			wnd->map_cp[y][x].y = y * wnd->cell;
			x_ = wnd->map_cp[y][x].x;
			y_ = wnd->map_cp[y][x].y;
			z_ = wnd->map[y][x].z;
			if (z_ && z_ > 0)
				z_ += wnd->z_shift;
			else if (z_ && z_ < 0)
				z_ -= wnd->z_shift;
				wnd->map_cp[y][x].y = y_  * wnd->cos_x + z_ * wnd->sin_x;
				wnd->map_cp[y][x].z = -y_ * wnd->sin_x + z_ * wnd->cos_x;

				x_ = wnd->map_cp[y][x].x;
				y_ = wnd->map_cp[y][x].y;
				z_ = wnd->map_cp[y][x].z;
				wnd->map_cp[y][x].x = x_  * wnd->cos_y + z_ * wnd->sin_y;
				wnd->map_cp[y][x].z = -x_ * wnd->sin_y + z_ * wnd->cos_y;

				x_ = wnd->map_cp[y][x].x;
				y_ = wnd->map_cp[y][x].y;
				z_ = wnd->map_cp[y][x].z;
				wnd->map_cp[y][x].x = x_ * wnd->cos_z - y_ * wnd->sin_z;
				wnd->map_cp[y][x].y = x_ * wnd->sin_z + y_ * wnd->cos_z;

				wnd->map_cp[y][x].x += wnd->x_offset;
				wnd->map_cp[y][x].y += wnd->y_offset;
		}

	pthread_exit(NULL);
}

void *change2(void *param)
{
	t_wnd *wnd = (t_wnd*)param;
	int x_;
	int y_;
	int z_;
for (size_t y = wnd->rows / 4; y < wnd->rows / 2; ++y)
		for (size_t x = 0; x < wnd->cols; ++x)
		{
			wnd->map_cp[y][x].x = x * wnd->cell;
			wnd->map_cp[y][x].y = y * wnd->cell;
			x_ = wnd->map_cp[y][x].x;
			y_ = wnd->map_cp[y][x].y;
			z_ = wnd->map[y][x].z;
			if (z_ && z_ > 0)
				z_ += wnd->z_shift;
			else if (z_ && z_ < 0)
				z_ -= wnd->z_shift;
				wnd->map_cp[y][x].y = y_  * wnd->cos_x + z_ * wnd->sin_x;
				wnd->map_cp[y][x].z = -y_ * wnd->sin_x + z_ * wnd->cos_x;

				x_ = wnd->map_cp[y][x].x;
				y_ = wnd->map_cp[y][x].y;
				z_ = wnd->map_cp[y][x].z;
				wnd->map_cp[y][x].x = x_  * wnd->cos_y + z_ * wnd->sin_y;
				wnd->map_cp[y][x].z = -x_ * wnd->sin_y + z_ * wnd->cos_y;

				x_ = wnd->map_cp[y][x].x;
				y_ = wnd->map_cp[y][x].y;
				z_ = wnd->map_cp[y][x].z;
				wnd->map_cp[y][x].x = x_ * wnd->cos_z - y_ * wnd->sin_z;
				wnd->map_cp[y][x].y = x_ * wnd->sin_z + y_ * wnd->cos_z;

				wnd->map_cp[y][x].x += wnd->x_offset;
				wnd->map_cp[y][x].y += wnd->y_offset;
		}
	pthread_exit(NULL);
}

void *change3(void *param)
{
	t_wnd *wnd = (t_wnd*)param;
	int x_;
	int y_;
	int z_;
for (size_t y = wnd->rows / 2; y < wnd->rows / 4 * 3; ++y)
		for (size_t x = 0; x < wnd->cols; ++x)
		{
			wnd->map_cp[y][x].x = x * wnd->cell;
			wnd->map_cp[y][x].y = y * wnd->cell;
			x_ = wnd->map_cp[y][x].x;
			y_ = wnd->map_cp[y][x].y;
			z_ = wnd->map[y][x].z;
			if (z_ && z_ > 0)
				z_ += wnd->z_shift;
			else if (z_ && z_ < 0)
				z_ -= wnd->z_shift;
				wnd->map_cp[y][x].y = y_  * wnd->cos_x + z_ * wnd->sin_x;
				wnd->map_cp[y][x].z = -y_ * wnd->sin_x + z_ * wnd->cos_x;

				x_ = wnd->map_cp[y][x].x;
				y_ = wnd->map_cp[y][x].y;
				z_ = wnd->map_cp[y][x].z;
				wnd->map_cp[y][x].x = x_  * wnd->cos_y + z_ * wnd->sin_y;
				wnd->map_cp[y][x].z = -x_ * wnd->sin_y + z_ * wnd->cos_y;

				x_ = wnd->map_cp[y][x].x;
				y_ = wnd->map_cp[y][x].y;
				z_ = wnd->map_cp[y][x].z;
				wnd->map_cp[y][x].x = x_ * wnd->cos_z - y_ * wnd->sin_z;
				wnd->map_cp[y][x].y = x_ * wnd->sin_z + y_ * wnd->cos_z;

				wnd->map_cp[y][x].x += wnd->x_offset;
				wnd->map_cp[y][x].y += wnd->y_offset;
		}
	pthread_exit(NULL);
}

void *change4(void *param)
{
	t_wnd *wnd = (t_wnd*)param;
	int x_;
	int y_;
	int z_;
for (size_t y = wnd->rows / 4 * 3; y < wnd->rows; ++y)
		for (size_t x = 0; x < wnd->cols; ++x)
		{
			wnd->map_cp[y][x].x = x * wnd->cell;
			wnd->map_cp[y][x].y = y * wnd->cell;
			x_ = wnd->map_cp[y][x].x;
			y_ = wnd->map_cp[y][x].y;
			z_ = wnd->map[y][x].z;
			// if (z_ && z_ > 0)
			// 	z_ += wnd->z_shift;
			// else if (z_ && z_ < 0)
			// 	z_ -= wnd->z_shift;
				wnd->map_cp[y][x].y = y_  * wnd->cos_x + z_ * wnd->sin_x;
				wnd->map_cp[y][x].z = -y_ * wnd->sin_x + z_ * wnd->cos_x;

				x_ = wnd->map_cp[y][x].x;
				y_ = wnd->map_cp[y][x].y;
				z_ = wnd->map_cp[y][x].z;
				wnd->map_cp[y][x].x = x_  * wnd->cos_y + z_ * wnd->sin_y;
				wnd->map_cp[y][x].z = -x_ * wnd->sin_y + z_ * wnd->cos_y;

				x_ = wnd->map_cp[y][x].x;
				y_ = wnd->map_cp[y][x].y;
				z_ = wnd->map_cp[y][x].z;
				wnd->map_cp[y][x].x = x_ * wnd->cos_z - y_ * wnd->sin_z;
				wnd->map_cp[y][x].y = x_ * wnd->sin_z + y_ * wnd->cos_z;

				wnd->map_cp[y][x].x += wnd->x_offset;
				wnd->map_cp[y][x].y += wnd->y_offset;
		}
	pthread_exit(NULL);
}


void change_angle(t_wnd *wnd)
{
	wnd->sin_x = sin(wnd->x_angle);
	wnd->sin_y = sin(wnd->y_angle);
	wnd->sin_z = sin(wnd->z_angle);
	wnd->cos_x = cos(wnd->x_angle);
	wnd->cos_z = cos(wnd->z_angle);
	wnd->cos_y = cos(wnd->y_angle);
	pthread_t thr1;
	pthread_t thr2;
	pthread_t thr3;
	pthread_t thr4;

	if (pthread_create(&thr1, NULL, change1, wnd))
		error(2, "cant create thread 1", "change_angle", 0);
	if (pthread_create(&thr2, NULL, change2, wnd))
		error(2, "cant create thread 2", "change_angle", 0);
	if (pthread_create(&thr3, NULL, change3, wnd))
		error(2, "cant create thread 3", "change_angle", 0);
	if (pthread_create(&thr4, NULL, change4, wnd))
		error(2, "cant create thread 4", "change_angle", 0);
}

t_wnd wnd_init(const char **argv)
{
	t_wnd wnd;

	ft_memset(&wnd, 0, sizeof(t_wnd));
	wnd.mlxptr = mlx_init();
	wnd.wndptr = mlx_new_window(wnd.mlxptr, WIDTH, HEIGHT, "fdf");
	wnd.imgptr = mlx_new_image(wnd.mlxptr, WIDTH, HEIGHT);
	wnd.img = mlx_get_data_addr(wnd.imgptr, &wnd.bytes, &wnd.size_line,
								&wnd.endian);
	wnd.bytes /= 8;
	wnd.cell = 1;
	wnd.map = get_map(argv[1]);
	wnd.map_cp = vec_cp(wnd.map);
	wnd.rows = vec_rows(wnd.map);
	wnd.cols = vec_size(wnd.map[0]);
	wnd.x_offset = WIDTH / 2 - vec_size(wnd.map[0]) * wnd.cell / 2;
	wnd.y_offset = HEIGHT / 2 - vec_rows(wnd.map) * wnd.cell / 2;
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
		wnd->x_center = wnd->cell + (vec_size(wnd->map[0]) * wnd->cell) / 2;
		wnd->y_center = wnd->cell + (vec_rows(wnd->map) * wnd->cell) / 2;
	}
	if (keycode != UP && keycode != DOWN && keycode != LEFT && keycode != RIGHT)
		change_angle(wnd);
	print_map(wnd);
	return (1);
}

int mouse_press(int button, int x, int y, t_wnd *wnd)
{
	if (button == 1 && x >= 0 && y >= 0 && x < MAX_X && y < MAX_Y)
	{
		wnd->is_mouse_active = 1;
		wnd->mouse_x = x;
		wnd->mouse_y = y;
	}
	else if (button == WHEEL_UP)
	{
		++wnd->cell;
		change_angle(wnd);
		print_map(wnd);
		return 1;
	}
	else if (button == WHEEL_DOWN && wnd->cell)
	{
		--wnd->cell;
		change_angle(wnd);
		print_map(wnd);
		return 1;
	}
	if (button == WHEEL_DOWN || button == WHEEL_UP)
	{
		change_angle(wnd);
		print_map(wnd);
	}
	return ((int)wnd);
}

int mouse_release(int button, int x, int y, t_wnd *wnd)
{
	if (button == 1)
		wnd->is_mouse_active = 0;
	return (x | y);
}

int mouse_move(int x, int y, t_wnd *wnd)
{
	if (wnd->is_mouse_active)
	{
		shift_map(wnd, x - wnd->mouse_x, y - wnd->mouse_y);
		wnd->mouse_x = x;
		wnd->mouse_y = y;
	}
	else
		return (1);
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
	mlx_hook(wnd.wndptr, 4, 1L << 2, mouse_press, &wnd);
	mlx_hook(wnd.wndptr, 5, 1L << 3, mouse_release, &wnd);
	mlx_hook(wnd.wndptr, 6, 1L << 13, mouse_move, &wnd);
	

	mlx_loop(wnd.mlxptr);





	return (0);
}
