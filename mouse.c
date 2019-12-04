/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbendu <dbendu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/03 21:12:32 by dbendu            #+#    #+#             */
/*   Updated: 2019/12/04 01:52:42 by dbendu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		mouse_press(int button, int x, int y, t_wnd *wnd)
{
	if ((button == LEFT_BUTTON || button == RIGHT_BUTTON) &&
		x >= 0 && y >= 0 && x < MAX_X && y < MAX_Y)
	{
		button == LEFT_BUTTON ? (wnd->mouse.is_left_button_active = 1) :
								(wnd->mouse.is_right_button_active = 1);
		wnd->mouse.x = x;
		wnd->mouse.y = y;
		return (1);
	}
	else if (button == WHEEL_UP)
		++wnd->cell;
	else if (button == WHEEL_DOWN && wnd->cell)
		--wnd->cell;
	rotate(wnd);
	draw_map(wnd);
	return (1);
}

int		mouse_release(int button, int x, int y, t_wnd *wnd)
{
	if (button == LEFT_BUTTON)
		wnd->mouse.is_left_button_active = 0;
	else if (button == RIGHT_BUTTON)
		wnd->mouse.is_right_button_active = 0;
	return (x | y);
}

int		mouse_move(int x, int y, t_wnd *wnd)
{
	if (wnd->mouse.is_left_button_active)
	{
		shift_map(wnd, x - wnd->mouse.x, y - wnd->mouse.y);
		wnd->mouse.x = x;
		wnd->mouse.y = y;
	}
	else if (wnd->mouse.is_right_button_active)
	{
		if (x > wnd->mouse.x)
			wnd->angles.y_angle += 3.14 / 360 * 6;
		else if (x < wnd->mouse.x)
			wnd->angles.y_angle -= 3.14 / 360 * 6;
		if (y > wnd->mouse.y)
			wnd->angles.x_angle -= 3.14 / 360 * 6;
		else if (y < wnd->mouse.y)
			wnd->angles.x_angle += 3.14 / 360 * 6;
		wnd->mouse.x = x;
		wnd->mouse.y = y;
		rotate(wnd);
	}
	else
		return (1);
	draw_map(wnd);
	return (1);
}
