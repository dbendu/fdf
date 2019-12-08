/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/03 20:41:06 by dbendu            #+#    #+#             */
/*   Updated: 2019/12/08 21:50:11 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void		key_press_2(int keycode, t_wnd *wnd)
{
	if (keycode == G)
		wnd->gradient = !wnd->gradient;
	if (keycode == LESS && wnd->bkg_color)
		wnd->bkg_color -= ((1 << 16) + (1 << 8) + 1);
	else if (keycode == MORE && wnd->bkg_color < (255 << 16) + (255 << 8) + 255)
		wnd->bkg_color += ((1 << 16) + (1 << 8) + 1);
	else if (keycode == ESC)
		fdf_exit(wnd);
	if ((wnd->bkg_color & 255) > 122)
		wnd->fill_color = __BLACK;
	else
		wnd->fill_color = __WHITE;
}

static void		key_press_1(int keycode, t_wnd *wnd)
{
	if (keycode == W)
		wnd->angles.x_angle += 3;
	else if (keycode == S)
		wnd->angles.x_angle -= 3;
	else if (keycode == A)
		wnd->angles.y_angle -= 3;
	else if (keycode == D)
		wnd->angles.y_angle += 3;
	else if (keycode == Q)
		wnd->angles.z_angle -= 3;
	else if (keycode == E)
		wnd->angles.z_angle += 3;
	else if (keycode == TAB)
		wnd->show_menu = !wnd->show_menu;
	else if (keycode == I)
		wnd->show_info = !wnd->show_info;
	else
		key_press_2(keycode, wnd);
	if (abs(wnd->angles.x_angle) == 360)
		wnd->angles.x_angle = 0;
	if (abs(wnd->angles.y_angle) == 360)
		wnd->angles.y_angle = 0;
	if (abs(wnd->angles.z_angle) == 360)
		wnd->angles.z_angle = 0;
}

int				key_press(int keycode, t_wnd *wnd)
{
	if (keycode == MINUS && wnd->cell)
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
