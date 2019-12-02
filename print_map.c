/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbendu <dbendu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/02 21:21:53 by dbendu            #+#    #+#             */
/*   Updated: 2019/12/02 21:23:54 by dbendu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	print_map(t_wnd *wnd)
{
	ft_memset(wnd->img, 0, wnd->size_line * HEIGHT);
	for (size_t y = 0; y < wnd->rows; ++y)
	{
		for (size_t x = 0; x < wnd->cols; ++x)
		{
			wnd->map_cp[y][x].a_color = wnd->map[y][x].a_color;
			wnd->map_cp[y][x].g_color = wnd->map[y][x].g_color;
			wnd->map_cp[y][x].b_color = wnd->map[y][x].b_color;
			if (x != wnd->cols - 1)
			{
				wnd->map_cp[y][x + 1].a_color = wnd->map[y][x + 1].a_color;
				wnd->map_cp[y][x + 1].g_color = wnd->map[y][x + 1].g_color;
				wnd->map_cp[y][x + 1].b_color = wnd->map[y][x + 1].b_color;
				draw_line(wnd, &wnd->map_cp[y][x], &wnd->map_cp[y][x + 1]);
			}
			if (y != wnd->rows - 1)
			{
				wnd->map_cp[y + 1][x].a_color = wnd->map_cp[y + 1][x].a_color;
				wnd->map_cp[y + 1][x].g_color = wnd->map_cp[y + 1][x].g_color;
				wnd->map_cp[y + 1][x].b_color = wnd->map_cp[y + 1][x].b_color;
				draw_line(wnd, &wnd->map_cp[y][x], &wnd->map_cp[y + 1][x]);
			}
		}
	}
	mlx_put_image_to_window(wnd->mlxptr, wnd->wndptr, wnd->imgptr, 0, 0);
}