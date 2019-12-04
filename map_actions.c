/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_actions.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbendu <dbendu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/03 20:45:08 by dbendu            #+#    #+#             */
/*   Updated: 2019/12/04 04:13:11 by dbendu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void		shift_map(t_wnd *wnd, int x_, int y_)
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

static void	set_angles(t_wnd *wnd)
{
	wnd->angles.sin_x = sin(wnd->angles.x_angle);
	wnd->angles.sin_y = sin(wnd->angles.y_angle);
	wnd->angles.sin_z = sin(wnd->angles.z_angle);
	wnd->angles.cos_x = cos(wnd->angles.x_angle);
	wnd->angles.cos_z = cos(wnd->angles.z_angle);
	wnd->angles.cos_y = cos(wnd->angles.y_angle);
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
	wnd->angles.z_x = -wnd->angles.sin_y;
	wnd->angles.z_y = wnd->angles.cos_y * wnd->angles.sin_x;
	wnd->angles.z_z = wnd->angles.cos_y * wnd->angles.cos_x;
}

void		rotate(t_wnd *wnd)
{
	pthread_t thr1;
	pthread_t thr2;
	pthread_t thr3;
	pthread_t thr4;

	set_angles(wnd);
	if (pthread_create(&thr1, NULL, rotate_thread1, wnd))
		error(2, "cant create thread", "rotate", 0);
	if (pthread_create(&thr2, NULL, rotate_thread2, wnd))
		error(2, "cant create thread", "rotate", 0);
	if (pthread_create(&thr3, NULL, rotate_thread3, wnd))
		error(2, "cant create thread", "rotate", 0);
	if (pthread_create(&thr4, NULL, rotate_thread4, wnd))
		error(2, "cant create thread", "rotate", 0);
	if (pthread_join(thr1, NULL))
		error(2, "cant exit thread", "rotate", 0);
	if (pthread_join(thr2, NULL))
		error(2, "cant exit thread", "rotate", 0);
	if (pthread_join(thr3, NULL))
		error(2, "cant exit thread", "rotate", 0);
	if (pthread_join(thr4, NULL))
		error(2, "cant exit thread", "rotate", 0);
}
