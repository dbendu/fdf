/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/03 19:57:31 by dbendu            #+#    #+#             */
/*   Updated: 2019/12/07 15:13:43 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void		draw_menu_box(t_wnd *wnd)
{
	t_point a;
	t_point b;

	a.x = 0;
	b.x = 500;
	a.y = HEIGHT - 295;
	b.y = HEIGHT - 295;
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
	a.y = HEIGHT - 295;
	b.y = MAX_Y;
	draw_line(wnd, a, b);
	++a.x;
	++b.x;
	draw_line(wnd, a, b);
}

static void		draw_menu(t_wnd *wnd)
{
	draw_menu_box(wnd);
	mlx_put_image_to_window(wnd->mlxptr, wnd->wndptr, wnd->imgptr, 0, 0);
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
	mlx_string_put(wnd->mlxptr, wnd->wndptr, 25, HEIGHT - 40, __WHITE,
					"tab - show / hide panel");
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
	if (!wnd->cell)
		mlx_string_put(wnd->mlxptr, wnd->wndptr, WIDTH / 2 - 150, HEIGHT / 2,
						__WHITE, "Cell size is 0, you cant see the map");
}
