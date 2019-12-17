/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_actions.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbendu <dbendu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/03 20:45:08 by dbendu            #+#    #+#             */
/*   Updated: 2019/12/17 16:09:41 by dbendu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void		shift_map(t_wnd *wnd, int x_, int y_)
{
	size_t rows;
	size_t cols;

	wnd->x_offset += x_;
	wnd->y_offset += y_;
	rows = vec_rows(wnd->map);
	cols = vec_size(wnd->map[0]);
	for (size_t y = 0; y < rows; ++y)
	{
		for (size_t x = 0; x < cols; ++x)
		{
			wnd->map_cp[y][x].x += x_;
			wnd->map_cp[y][x].y += y_;
		}
	}
}

static void	set_angles(t_wnd *wnd)
{
	wnd->angles.sin_x = sin(wnd->angles.x_angle * 3.14 / 180);
	wnd->angles.sin_y = sin(wnd->angles.y_angle * 3.14 / 180);
	wnd->angles.sin_z = sin(wnd->angles.z_angle * 3.14 / 180);
	wnd->angles.cos_x = cos(wnd->angles.x_angle * 3.14 / 180);
	wnd->angles.cos_z = cos(wnd->angles.z_angle * 3.14 / 180);
	wnd->angles.cos_y = cos(wnd->angles.y_angle * 3.14 / 180);
	wnd->angles.x_x = wnd->angles.cos_z * wnd->angles.cos_y;
	wnd->angles.x_y = -wnd->angles.sin_z * wnd->angles.cos_x +
				wnd->angles.cos_z * wnd->angles.sin_y * wnd->angles.sin_x;
	wnd->angles.x_z = wnd->angles.sin_z * wnd->angles.sin_x +
				wnd->angles.cos_z * wnd->angles.sin_y * wnd->angles.cos_x;
	wnd->angles.y_x = wnd->angles.sin_z * wnd->angles.cos_y;
	wnd->angles.y_y = wnd->angles.cos_z * wnd->angles.cos_x +
				wnd->angles.sin_x * wnd->angles.sin_y * wnd->angles.sin_z;
	wnd->angles.y_z = -wnd->angles.cos_z * wnd->angles.sin_x +
				wnd->angles.sin_z * wnd->angles.sin_y * wnd->angles.cos_x;
}

void			rotate(t_wnd *wnd)
{
	t_int32 x_;
	t_int32 y_;

	set_angles(wnd);
	if (wnd->threads)
		rotate_threads(wnd);
	else
	{
		for (size_t y = 0; y < wnd->rows; ++y)
		{
			for (size_t x = 0; x < wnd->cols; ++x)
			{
				wnd->map_cp[y][x].y = y * wnd->cell - wnd->rows * wnd->cell / 2;
				wnd->map_cp[y][x].x = x * wnd->cell - wnd->cols * wnd->cell / 2;
				x_ = wnd->map_cp[y][x].x;
				y_ = wnd->map_cp[y][x].y;
				wnd->map_cp[y][x].x = x_ * wnd->angles.x_x + y_ * wnd->angles.x_y +
				wnd->map[y][x].z * wnd->angles.x_z;
				wnd->map_cp[y][x].y = x_ * wnd->angles.y_x + y_ * wnd->angles.y_y +
				wnd->map[y][x].z * wnd->angles.y_z;
				wnd->map_cp[y][x].x += wnd->x_offset;
				wnd->map_cp[y][x].y += wnd->y_offset;
			}
		}
	}
}
