/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/04 03:44:47 by dbendu            #+#    #+#             */
/*   Updated: 2019/12/08 21:50:01 by user             ###   ########.fr       */
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

	wnd = (t_wnd*)param;
	for (size_t y = 0; y < wnd->rows / 4; ++y)
		for (size_t x = 0; x < wnd->cols; ++x)
			eval(wnd, x, y);
	pthread_exit(NULL);
}

void		*rotate_thread2(void *param)
{
	t_wnd	*wnd;

	wnd = (t_wnd*)param;
	for (size_t y = wnd->rows / 4; y < wnd->rows / 2; ++y)
		for (size_t x = 0; x < wnd->cols; ++x)
			eval(wnd, x, y);
	pthread_exit(NULL);
}

void		*rotate_thread3(void *param)
{
	t_wnd	*wnd;

	wnd = (t_wnd*)param;
	for (size_t y = wnd->rows / 2; y < wnd->rows / 4 * 3; ++y)
		for (size_t x = 0; x < wnd->cols; ++x)
			eval(wnd, x, y);
	pthread_exit(NULL);
}

void		*rotate_thread4(void *param)
{
	t_wnd	*wnd;

	wnd = (t_wnd*)param;
	for (size_t y = wnd->rows / 4 * 3; y < wnd->rows; ++y)
		for (size_t x = 0; x < wnd->cols; ++x)
			eval(wnd, x, y);
	pthread_exit(NULL);
}

void		rotate_threads(t_wnd *wnd)
{
	pthread_t thr1;
	pthread_t thr2;
	pthread_t thr3;
	pthread_t thr4;

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
