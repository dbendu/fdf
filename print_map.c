/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbendu <dbendu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/02 21:21:53 by dbendu            #+#    #+#             */
/*   Updated: 2019/12/03 00:03:51 by dbendu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>

#include "fdf.h"

void *print1(void *param)
{
	t_wnd *wnd = (t_wnd*)param;

	for (int y = (int)wnd->rows / 4; y >= 0; --y)
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
				wnd->map_cp[y + 1][x].a_color = wnd->map_cp[y + 1][x].a_color;
				wnd->map_cp[y + 1][x].g_color = wnd->map_cp[y + 1][x].g_color;
				wnd->map_cp[y + 1][x].b_color = wnd->map_cp[y + 1][x].b_color;
				draw_line(wnd, &wnd->map_cp[y][x], &wnd->map_cp[y + 1][x]);
		}
	}

	pthread_exit(NULL);
}

void *print2(void *param)
{
	usleep(100000);
	t_wnd *wnd = (t_wnd*)param;

	for (int y = (int)wnd->rows / 2; y > (int)wnd->rows / 4; --y)
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
				wnd->map_cp[y + 1][x].a_color = wnd->map_cp[y + 1][x].a_color;
				wnd->map_cp[y + 1][x].g_color = wnd->map_cp[y + 1][x].g_color;
				wnd->map_cp[y + 1][x].b_color = wnd->map_cp[y + 1][x].b_color;
				draw_line(wnd, &wnd->map_cp[y][x], &wnd->map_cp[y + 1][x]);
		}
	}

	pthread_exit(NULL);
}

void *print3(void *param)
{
	usleep(200000);
	t_wnd *wnd = (t_wnd*)param;

	for (int y = (int)wnd->rows / 4 * 3; y > (int)wnd->rows / 2; --y)
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
				wnd->map_cp[y + 1][x].a_color = wnd->map_cp[y + 1][x].a_color;
				wnd->map_cp[y + 1][x].g_color = wnd->map_cp[y + 1][x].g_color;
				wnd->map_cp[y + 1][x].b_color = wnd->map_cp[y + 1][x].b_color;
				draw_line(wnd, &wnd->map_cp[y][x], &wnd->map_cp[y + 1][x]);
		}
	}

	pthread_exit(NULL);
}

void *print4(void *param)
{
	usleep(300000);
	t_wnd *wnd = (t_wnd*)param;

	for (int y = (int)wnd->rows - 1; y > (int)wnd->rows / 4 * 3; --y)
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
			if (y != (int)wnd->rows - 1)
			{
				wnd->map_cp[y + 1][x].a_color = wnd->map_cp[y + 1][x].a_color;
				wnd->map_cp[y + 1][x].g_color = wnd->map_cp[y + 1][x].g_color;
				wnd->map_cp[y + 1][x].b_color = wnd->map_cp[y + 1][x].b_color;
				draw_line(wnd, &wnd->map_cp[y][x], &wnd->map_cp[y + 1][x]);
			}
		}
	}

	pthread_exit(NULL);
}

void	print_map(t_wnd *wnd)
{
	pthread_t thr1;
	pthread_t thr2;
	pthread_t thr3;
	pthread_t thr4;
	
	ft_memset(wnd->img, 0, wnd->size_line * HEIGHT);

	if (pthread_create(&thr1, NULL, print1, wnd))
		error(2, "cant create thread 1", "change_angle", 0);
	if (pthread_create(&thr2, NULL, print2, wnd))
		error(2, "cant create thread 2", "change_angle", 0);
	if (pthread_create(&thr3, NULL, print3, wnd))
		error(2, "cant create thread 3", "change_angle", 0);
	if (pthread_create(&thr4, NULL, print4, wnd))
		error(2, "cant create thread 4", "change_angle", 0);

	if (pthread_join(thr1, NULL))
		error(2, "AAAAA", NULL, 0);
	if (pthread_join(thr2, NULL))
		error(2, "AAAAA", NULL, 0);
	if (pthread_join(thr3, NULL))
		error(2, "AAAAA", NULL, 0);
	if (pthread_join(thr4, NULL))
		error(2, "AAAAA", NULL, 0);
	
	mlx_put_image_to_window(wnd->mlxptr, wnd->wndptr, wnd->imgptr, 0, 0);
}

// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   print_map.c                                        :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: dbendu <dbendu@student.42.fr>              +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2019/12/02 21:21:53 by dbendu            #+#    #+#             */
// /*   Updated: 2019/12/02 21:23:54 by dbendu           ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

// #include "fdf.h"

// void	print_map(t_wnd *wnd)
// {
// 	ft_memset(wnd->img, 0, wnd->size_line * HEIGHT);
// 	for (size_t y = 0; y < wnd->rows; ++y)
// 	{
// 		for (size_t x = 0; x < wnd->cols; ++x)
// 		{
// 			wnd->map_cp[y][x].a_color = wnd->map[y][x].a_color;
// 			wnd->map_cp[y][x].g_color = wnd->map[y][x].g_color;
// 			wnd->map_cp[y][x].b_color = wnd->map[y][x].b_color;
// 			if (x != wnd->cols - 1)
// 			{
// 				wnd->map_cp[y][x + 1].a_color = wnd->map[y][x + 1].a_color;
// 				wnd->map_cp[y][x + 1].g_color = wnd->map[y][x + 1].g_color;
// 				wnd->map_cp[y][x + 1].b_color = wnd->map[y][x + 1].b_color;
// 				draw_line(wnd, &wnd->map_cp[y][x], &wnd->map_cp[y][x + 1]);
// 			}
// 			if (y != wnd->rows - 1)
// 			{
// 				wnd->map_cp[y + 1][x].a_color = wnd->map_cp[y + 1][x].a_color;
// 				wnd->map_cp[y + 1][x].g_color = wnd->map_cp[y + 1][x].g_color;
// 				wnd->map_cp[y + 1][x].b_color = wnd->map_cp[y + 1][x].b_color;
// 				draw_line(wnd, &wnd->map_cp[y][x], &wnd->map_cp[y + 1][x]);
// 			}
// 		}
// 	}
// 	mlx_put_image_to_window(wnd->mlxptr, wnd->wndptr, wnd->imgptr, 0, 0);
// }