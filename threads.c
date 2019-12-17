/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbendu <dbendu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/04 03:44:47 by dbendu            #+#    #+#             */
/*   Updated: 2019/12/17 16:37:18 by dbendu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void		*rotate_thread(void *param)
{
	t_threads	*threads_data;
	t_wnd		*wnd;
	t_int32		x_;
	t_int32	y_;

	threads_data = (t_threads*)param;
	wnd = threads_data->wnd;
	for (size_t y = threads_data->y_beg; y < threads_data->y_end; ++y)
		for (size_t x = 0; x < threads_data->wnd->cols; ++x)
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
	pthread_exit(NULL);
}

void		rotate_threads(t_wnd *wnd)
{
	t_threads	threads[4];

	for (size_t i = 0; i < 4; ++i)
	{
		threads[i].wnd = wnd;
		threads[i].y_beg = wnd->rows * i / 4;
		threads[i].y_end = wnd->rows * (i + 1) / 4;
		if (pthread_create(&(threads[i].thread), NULL, rotate_thread,
							&(threads[i])))
			error(2, "cant create thread", "rotate", 0);
	}
	for (size_t i = 0; i < 4; ++i)
		if (pthread_join(threads[i].thread, NULL))
			error(2, "cant exit thread", "rotate", 0);
}
