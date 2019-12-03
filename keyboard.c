/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbendu <dbendu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/03 20:41:06 by dbendu            #+#    #+#             */
/*   Updated: 2019/12/03 20:42:13 by dbendu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void		key_press_1(int keycode, t_wnd *wnd)
{
	if (keycode == W)
		wnd->angles.x_angle += 3.14 / 360 * 6;
	else if (keycode == S)
		wnd->angles.x_angle -= 3.14 / 360 * 6;
	else if (keycode == A)
		wnd->angles.y_angle -= 3.14 / 360 * 6;
	else if (keycode == D)
		wnd->angles.y_angle += 3.14 / 360 * 6;
	else if (keycode == Q)
		wnd->angles.z_angle -= 3.14 / 360 * 6;
	else if (keycode == E)
		wnd->angles.z_angle += 3.14 / 360 * 6;
	else if (keycode == TAB)
		wnd->show_menu = !wnd->show_menu;
}

int			key_press(int keycode, t_wnd *wnd)
{
	if (keycode == ESC)
		fdf_exit(wnd);
	else if (keycode == MINUS)
		--wnd->cell;
	else if (keycode == PLUS)
		++wnd->cell;
	else if (keycode == UP)
		shift_map(wnd, 0, -50);
	else if (keycode == DOWN)
		shift_map(wnd, 0, 50);
	else if (keycode == LEFT)
		shift_map(wnd, -50, 0);
	else if (keycode == RIGHT)
		shift_map(wnd, 50, 0);
	else if (keycode == SPACE)
	{
		wnd->angles.x_angle = 0;
		wnd->angles.y_angle = 0;
		wnd->angles.z_angle = 0;
	}
	else
		key_press_1(keycode, wnd);
	if (keycode != UP && keycode != DOWN && keycode != LEFT && keycode != RIGHT)
		rotate(wnd);
	draw_map(wnd);
	return (1);
}