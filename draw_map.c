/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/03 19:57:31 by dbendu            #+#    #+#             */
/*   Updated: 2019/12/07 22:05:33 by user             ###   ########.fr       */
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
		ft_memset(wnd->img + wnd->size_line * i, wnd->bkg_color, 500 * wnd->bytes);
	ft_memset(wnd->img + wnd->size_line * (HEIGHT - 300), wnd->fill_color, 500 * wnd->bytes);
	ft_memset(wnd->img + wnd->size_line * (HEIGHT - 299), wnd->fill_color, 500 * wnd->bytes);
	a.red = (wnd->fill_color >> 16) & 255;
	a.blue = (wnd->fill_color >> 8) & 255;
	a.green = wnd->fill_color & 255;
	b.red = (wnd->fill_color >> 16) & 255;
	b.blue = (wnd->fill_color >> 8) & 255;
	b.green = wnd->fill_color & 255;
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

	i = HEIGHT - 300;
	while (++i <= HEIGHT)
		ft_memset(wnd->img + wnd->size_line * i - 500 * wnd->bytes, wnd->bkg_color, 500 * wnd->bytes);
	ft_memset(wnd->img + wnd->size_line * (HEIGHT - 299) - 500 * wnd->bytes, wnd->fill_color, 500 * wnd->bytes);
	ft_memset(wnd->img + wnd->size_line * (HEIGHT - 298) - 500 * wnd->bytes, wnd->fill_color, 500 * wnd->bytes);
	a.red = (wnd->fill_color >> 16) & 255;
	a.blue = (wnd->fill_color >> 8) & 255;
	a.green = wnd->fill_color & 255;
	b.red = (wnd->fill_color >> 16) & 255;
	b.blue = (wnd->fill_color >> 8) & 255;
	b.green = wnd->fill_color & 255;
	a.x = WIDTH - 502;
	b.x = a.x;
	a.y = HEIGHT - 300;
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
		mlx_string_put(wnd->mlxptr, wnd->wndptr, 25, HEIGHT - 280, wnd->fill_color,
						"w, s - rotate x");
		mlx_string_put(wnd->mlxptr, wnd->wndptr, 25, HEIGHT - 250, wnd->fill_color,
						"a, d - rotate y");
		mlx_string_put(wnd->mlxptr, wnd->wndptr, 25, HEIGHT - 220, wnd->fill_color,
						"q, e - rotate z");
		mlx_string_put(wnd->mlxptr, wnd->wndptr, 25, HEIGHT - 190, wnd->fill_color,
						"-, +, mouse wheel - change zoom");
		mlx_string_put(wnd->mlxptr, wnd->wndptr, 25, HEIGHT - 160, wnd->fill_color,
						"arrows / left mouse button + move - move map");
		mlx_string_put(wnd->mlxptr, wnd->wndptr, 25, HEIGHT - 130, wnd->fill_color,
						"right mouse button + move - rotate x / y");
		mlx_string_put(wnd->mlxptr, wnd->wndptr, 25, HEIGHT - 100, wnd->fill_color,
						"space - reset rotate");
		mlx_string_put(wnd->mlxptr, wnd->wndptr, 25, HEIGHT - 70, wnd->fill_color,
						"i - show / hide info");
		mlx_string_put(wnd->mlxptr, wnd->wndptr, 25, HEIGHT - 20, wnd->fill_color,
						"tab - show / hide panel");
	}
	if (wnd->show_info)
	{
		char *str = malloc(100);
		sprintf(str, "x angle: %d", wnd->angles.x_angle);
		mlx_string_put(wnd->mlxptr, wnd->wndptr, WIDTH - 480, HEIGHT - 280, wnd->fill_color,
						str);
		sprintf(str, "y angle: %d", wnd->angles.y_angle);
		mlx_string_put(wnd->mlxptr, wnd->wndptr, WIDTH - 480, HEIGHT - 250, wnd->fill_color,
						str);
		sprintf(str, "z angle: %d", wnd->angles.z_angle);
		mlx_string_put(wnd->mlxptr, wnd->wndptr, WIDTH - 480, HEIGHT - 220, wnd->fill_color,
						str);
		sprintf(str, "cell: %d", wnd->cell);
		mlx_string_put(wnd->mlxptr, wnd->wndptr, WIDTH - 480, HEIGHT - 190, wnd->fill_color,
						str);
		sprintf(str, "map size: %dx%d", wnd->rows, wnd->cols);
		mlx_string_put(wnd->mlxptr, wnd->wndptr, WIDTH - 480, HEIGHT - 120, wnd->fill_color,
						str);
		free(str);
	}
	if (!wnd->cell)
		mlx_string_put(wnd->mlxptr, wnd->wndptr, WIDTH / 2 - 150, HEIGHT / 2,
						wnd->fill_color, "Cell size is 0, you cant see the map");
}

void			draw_map(t_wnd *wnd)
{
	int	y;
	int	x;

	ft_memset(wnd->img, wnd->bkg_color, wnd->size_line * HEIGHT);
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
	if (wnd->show_menu)
		draw_menu_box(wnd);
	if (wnd->show_info)
		draw_info_box(wnd);
	mlx_put_image_to_window(wnd->mlxptr, wnd->wndptr, wnd->imgptr, 0, 0);
	show_text(wnd);
}
