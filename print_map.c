/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbendu <dbendu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/03 19:57:31 by dbendu            #+#    #+#             */
/*   Updated: 2019/12/03 21:53:30 by dbendu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void		draw_box(t_wnd *wnd)
{
	t_point a;
	t_point b;

	a.x = 0;
	b.x = 500;
	a.y = HEIGHT - 250;
	b.y = HEIGHT - 250;
	a.red = 255;
	a.blue = 255;
	a.green = 255;
	b.red = 255;
	b.blue = 255;
	b.green = 255;
	draw_line(wnd, a, b);
	++a.y;
	++b.y;
	draw_line(wnd, a, b);
	a.x = 500;
	a.y = HEIGHT - 250;
	b.y = MAX_Y;
	draw_line(wnd, a, b);
	++a.x;
	++b.x;
	draw_line(wnd, a, b);
}

static void		draw_menu(t_wnd *wnd)
{
	draw_box(wnd);
	mlx_put_image_to_window(wnd->mlxptr, wnd->wndptr, wnd->imgptr, 0, 0);
	mlx_string_put(wnd->mlxptr, wnd->wndptr, 25, HEIGHT - 225, __white,
					"tab - show / hide panel");
	mlx_string_put(wnd->mlxptr, wnd->wndptr, 25, HEIGHT - 200, __white,
					"w, s - rotate x");
	mlx_string_put(wnd->mlxptr, wnd->wndptr, 25, HEIGHT - 175, __white,
					"a, d - rotate y");
	mlx_string_put(wnd->mlxptr, wnd->wndptr, 25, HEIGHT - 150, __white,
					"q, e - rotate z");
	mlx_string_put(wnd->mlxptr, wnd->wndptr, 25, HEIGHT - 125, __white,
					"-, +, mouse wheel - change zoom");
	mlx_string_put(wnd->mlxptr, wnd->wndptr, 25, HEIGHT - 100, __white,
					"arrows / left mouse button + move - move map");
	mlx_string_put(wnd->mlxptr, wnd->wndptr, 25, HEIGHT - 75, __white,
					"space - reset rotate");
}

void			draw_map(t_wnd *wnd)
{
	int	y;
	int	x;

	ft_memset(wnd->img, 0, wnd->size_line * HEIGHT);
	y = -1;
	if (wnd->cell)
		while (++y < wnd->rows)
		{
			x = -1;
			while (++x < wnd->cols)
			{
				if (x != wnd->cols - 1)
					draw_line(wnd, wnd->map_cp[y][x], wnd->map_cp[y][x + 1]);
				if (y != wnd->rows - 1)
					draw_line(wnd, wnd->map_cp[y][x], wnd->map_cp[y + 1][x]);
			}
		}
	mlx_put_image_to_window(wnd->mlxptr, wnd->wndptr, wnd->imgptr, 0, 0);
	if (wnd->show_menu)
		draw_menu(wnd);
}
