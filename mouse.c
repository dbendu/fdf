/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbendu <dbendu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/03 21:12:32 by dbendu            #+#    #+#             */
/*   Updated: 2019/12/03 21:12:46 by dbendu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int mouse_press(int button, int x, int y, t_wnd *wnd)
{
	if (button == 1 && x >= 0 && y >= 0 && x < MAX_X && y < MAX_Y)
	{
		wnd->is_mouse_active = 1;
		wnd->mouse_x = x;
		wnd->mouse_y = y;
	}
	else if (button == WHEEL_UP)
	{
		++wnd->cell;
		rotate(wnd);
		draw_map(wnd);
		return 1;
	}
	else if (button == WHEEL_DOWN && wnd->cell)
	{
		--wnd->cell;
		rotate(wnd);
		draw_map(wnd);
		return 1;
	}
	if (button == WHEEL_DOWN || button == WHEEL_UP)
	{
		rotate(wnd);
		draw_map(wnd);
	}
	return (*(int*)wnd);
}

int mouse_release(int button, int x, int y, t_wnd *wnd)
{
	if (button == 1)
		wnd->is_mouse_active = 0;
	return (x | y);
}

int mouse_move(int x, int y, t_wnd *wnd)
{
	if (wnd->is_mouse_active)
	{
		shift_map(wnd, x - wnd->mouse_x, y - wnd->mouse_y);
		wnd->mouse_x = x;
		wnd->mouse_y = y;
	}
	else
		return (1);
	draw_map(wnd);
	return (1);
}