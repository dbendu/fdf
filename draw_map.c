/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbendu <dbendu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/03 19:57:31 by dbendu            #+#    #+#             */
/*   Updated: 2019/12/16 21:41:24 by dbendu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "fdf.h"

static void		draw_menu_box(t_wnd *wnd)
{
	t_point	a;
	t_point	b;
	size_t	i;

	i = HEIGHT - 299;
	while (++i < HEIGHT)
		ft_memset(wnd->img + wnd->size_line * i, __BLACK, 500 * wnd->bytes);
	a.red = __WHITE;
	a.blue = __WHITE;
	a.green = __WHITE;
	b.red = __WHITE;
	b.blue = __WHITE;
	b.green = __WHITE;
	a.x = 0;
	b.x = 499;
	a.y = HEIGHT - 300;
	b.y = a.y;
	draw_line(wnd, a, b);
	++a.y;
	++b.y;
	draw_line(wnd, a, b);
	a.x = 498;
	b.x = a.x;
	a.y = HEIGHT - 298;
	b.y = MAX_Y;
	draw_line(wnd, a, b);
	++a.x;
	++b.x;
	draw_line(wnd, a, b);
}

static void		draw_info_box(t_wnd *wnd)
{
	t_point	a;
	t_point	b;
	size_t	i;

	i = HEIGHT - 299;
	while (++i <= HEIGHT)
		ft_memset(wnd->img + wnd->size_line * i - 500 * wnd->bytes, __BLACK, 500 * wnd->bytes);
	a.x = MAX_X - 500;
	b.x = MAX_X;
	a.y = HEIGHT - 300;
	b.y = a.y;
	a.red = __WHITE;
	a.blue = __WHITE;
	a.green = __WHITE;
	b.red = __WHITE;
	b.blue = __WHITE;
	b.green = __WHITE;
	draw_line(wnd, a, b);
	++a.y;
	++b.y;
	draw_line(wnd, a, b);
	a.y = HEIGHT - 300;
	b.x = a.x;
	b.y = MAX_Y;
	draw_line(wnd, a, b);
	++a.x;
	++b.x;
	draw_line(wnd, a, b);
}

static void		show_text(t_wnd *wnd)
{
	if (wnd->show_menu)
	{
		mlx_string_put(wnd->mlxptr, wnd->wndptr, 25, HEIGHT - 280, __WHITE,
						"w, s - rotate x");
		mlx_string_put(wnd->mlxptr, wnd->wndptr, 25, HEIGHT - 250, __WHITE,
						"a, d - rotate y");
		mlx_string_put(wnd->mlxptr, wnd->wndptr, 25, HEIGHT - 220, __WHITE,
						"q, e - rotate z");
		mlx_string_put(wnd->mlxptr, wnd->wndptr, 25, HEIGHT - 190, __WHITE,
						"-, +, mouse wheel - change zoom");
		mlx_string_put(wnd->mlxptr, wnd->wndptr, 25, HEIGHT - 160, __WHITE,
						"arrows / left mouse button + move - move map");
		mlx_string_put(wnd->mlxptr, wnd->wndptr, 25, HEIGHT - 130, __WHITE,
						"right mouse button + move - rotate x / y");
		mlx_string_put(wnd->mlxptr, wnd->wndptr, 25, HEIGHT - 100, __WHITE,
						"space - reset rotate");
		mlx_string_put(wnd->mlxptr, wnd->wndptr, 25, HEIGHT - 70, __WHITE,
						"i - show / hide info");
		mlx_string_put(wnd->mlxptr, wnd->wndptr, 25, HEIGHT - 20, __WHITE,
						"tab - show / hide panel");
	}
	if (wnd->show_info)
	{
		char *str = malloc(100);
		sprintf(str, "x angle: %d", wnd->angles.x_angle);
		mlx_string_put(wnd->mlxptr, wnd->wndptr, WIDTH - 480, HEIGHT - 280, __WHITE,
						str);
		sprintf(str, "y angle: %d", wnd->angles.y_angle);
		mlx_string_put(wnd->mlxptr, wnd->wndptr, WIDTH - 480, HEIGHT - 250, __WHITE,
						str);
		sprintf(str, "z angle: %d", wnd->angles.z_angle);
		mlx_string_put(wnd->mlxptr, wnd->wndptr, WIDTH - 480, HEIGHT - 220, __WHITE,
						str);
		sprintf(str, "cell size: %d", wnd->cell);
		mlx_string_put(wnd->mlxptr, wnd->wndptr, WIDTH - 480, HEIGHT - 190, __WHITE,
						str);
		sprintf(str, "map size: %zux%zu", wnd->rows, wnd->cols);
		mlx_string_put(wnd->mlxptr, wnd->wndptr, WIDTH - 480, HEIGHT - 50, __WHITE,
						str);
		sprintf(str, "threads: %s", wnd->threads ? "on" : "off");
		mlx_string_put(wnd->mlxptr, wnd->wndptr, WIDTH - 480, HEIGHT - 20, __WHITE,
						str);
		free(str);
	}
	if (!wnd->cell)
		mlx_string_put(wnd->mlxptr, wnd->wndptr, WIDTH / 2 - 150, HEIGHT / 2,
						__WHITE, "Cell size is 0, you cant see the map");
}

void			draw_map(t_wnd *wnd)
{
	ft_memset(wnd->img, __BLACK, wnd->size_line * HEIGHT);
	if (wnd->cell)
		for (size_t y = 0; y < wnd->rows; ++y)
			for (size_t x = 0; x < wnd->cols; ++x)
			{
				if (x != wnd->cols - 1)
					draw_line(wnd, wnd->map_cp[y][x], wnd->map_cp[y][x + 1]);
				if (y != wnd->rows - 1)
					draw_line(wnd, wnd->map_cp[y][x], wnd->map_cp[y + 1][x]);
			}
	if (wnd->show_menu)
		draw_menu_box(wnd);
	if (wnd->show_info)
		draw_info_box(wnd);
	mlx_put_image_to_window(wnd->mlxptr, wnd->wndptr, wnd->imgptr, 0, 0);
	show_text(wnd);
}
