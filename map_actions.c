/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_actions.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbendu <dbendu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/03 20:45:08 by dbendu            #+#    #+#             */
/*   Updated: 2019/12/03 21:11:04 by dbendu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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

static void set_angles(t_wnd *wnd)
{
	wnd->angles.sin_x = sin(wnd->angles.x_angle);
	wnd->angles.sin_y = sin(wnd->angles.y_angle);
	wnd->angles.sin_z = sin(wnd->angles.z_angle);
	wnd->angles.cos_x = cos(wnd->angles.x_angle);
	wnd->angles.cos_z = cos(wnd->angles.z_angle);
	wnd->angles.cos_y = cos(wnd->angles.y_angle);
	wnd->angles.czcy = wnd->angles.cos_z * wnd->angles.cos_y;
	wnd->angles.szcx = -wnd->angles.sin_z * wnd->angles.cos_x;
	wnd->angles.czsysx = wnd->angles.cos_z * wnd->angles.sin_y *
														wnd->angles.sin_x;
	wnd->angles.szsx = wnd->angles.sin_z * wnd->angles.sin_x;
	wnd->angles.czsycx = wnd->angles.cos_z * wnd->angles.sin_y *
														wnd->angles.cos_x;
	wnd->angles.szcy = wnd->angles.sin_z * wnd->angles.cos_y;
	wnd->angles.czcx = wnd->angles.cos_z * wnd->angles.cos_x;
	wnd->angles.sxsysz = wnd->angles.sin_x * wnd->angles.sin_y *
														wnd->angles.sin_z;
	wnd->angles.czsx = -wnd->angles.cos_z * wnd->angles.sin_x;
	wnd->angles.szsycx = wnd->angles.sin_z * wnd->angles.sin_y *
														wnd->angles.cos_x;
	wnd->angles.cysx = wnd->angles.cos_y * wnd->angles.sin_x;
	wnd->angles.cycx = wnd->angles.cos_y * wnd->angles.cos_x;
}

void rotate(t_wnd *wnd)
{
	int x_;
	int y_;
	int z_;
	int y;
	int x;

	set_angles(wnd);
	y = -1;
	while (++y < wnd->rows)
	{
		x = -1;
		while (++x < wnd->cols)
		{
			wnd->map_cp[y][x].y = y * wnd->cell - wnd->rows * wnd->cell / 2;
			wnd->map_cp[y][x].x = x * wnd->cell - wnd->cols * wnd->cell / 2;
			x_ = wnd->map_cp[y][x].x;
			y_ = wnd->map_cp[y][x].y;
			z_ = wnd->map[y][x].z;
			wnd->map_cp[y][x].x = x_ * wnd->angles.czcy + y_ * (wnd->angles.szcx
+ wnd->angles.czsysx) + z_ * (wnd->angles.szsx + wnd->angles.czsycx) + wnd->x_offset;
			wnd->map_cp[y][x].y = x_ * wnd->angles.szcy + y_ * (wnd->angles.czcx
+ wnd->angles.sxsysz) + z_ * (wnd->angles.czsx + wnd->angles.szsycx) + wnd->y_offset;
			wnd->map_cp[y][x].z = x_ * -wnd->angles.sin_y
		+ y_ * wnd->angles.cysx + z_ * wnd->angles.cycx;
		}
	}
}