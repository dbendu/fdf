/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbendu <dbendu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/04 03:44:47 by dbendu            #+#    #+#             */
/*   Updated: 2019/12/04 03:49:19 by dbendu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	eval(t_wnd *wnd, int x, int y)
{
	int x_;
	int y_;

	wnd->map_cp[y][x].y = y * wnd->cell - wnd->rows * wnd->cell / 2;
	wnd->map_cp[y][x].x = x * wnd->cell - wnd->cols * wnd->cell / 2;
	x_ = wnd->map_cp[y][x].x;
	y_ = wnd->map_cp[y][x].y;
	wnd->map_cp[y][x].x = x_ * wnd->angles.x_x + y_ * wnd->angles.x_y +
	wnd->map[y][x].z * wnd->angles.x_z;
	wnd->map_cp[y][x].y = x_ * wnd->angles.y_x + y_ * wnd->angles.y_y +
	wnd->map[y][x].z * wnd->angles.y_z;
	wnd->map_cp[y][x].z = x_ * wnd->angles.z_x + y_ * wnd->angles.z_y +
	wnd->map[y][x].z * wnd->angles.z_z;
	wnd->map_cp[y][x].x += wnd->x_offset;
	wnd->map_cp[y][x].y += wnd->y_offset;
}

void		*rotate_thread1(void *param)
{
	t_wnd	*wnd;
	int		y;
	int		x;

	wnd = (t_wnd*)param;
	y = -1;
	while (++y < wnd->rows / 4)
	{
		x = -1;
		while (++x < wnd->cols)
			eval(wnd, x, y);
	}
	pthread_exit(NULL);
}

void		*rotate_thread2(void *param)
{
	t_wnd	*wnd;
	int		y;
	int		x;

	wnd = (t_wnd*)param;
	y = wnd->rows / 4 - 1;
	while (++y < wnd->rows / 2)
	{
		x = -1;
		while (++x < wnd->cols)
			eval(wnd, x, y);
	}
	pthread_exit(NULL);
}

void		*rotate_thread3(void *param)
{
	t_wnd	*wnd;
	int		y;
	int		x;

	wnd = (t_wnd*)param;
	y = wnd->rows / 2 - 1;
	while (++y < wnd->rows / 4 * 3)
	{
		x = -1;
		while (++x < wnd->cols)
			eval(wnd, x, y);
	}
	pthread_exit(NULL);
}

void		*rotate_thread4(void *param)
{
	t_wnd	*wnd;
	int		y;
	int		x;

	wnd = (t_wnd*)param;
	y = wnd->rows / 4 * 3 - 1;
	while (++y < wnd->rows)
	{
		x = -1;
		while (++x < wnd->cols)
			eval(wnd, x, y);
	}
	pthread_exit(NULL);
}
