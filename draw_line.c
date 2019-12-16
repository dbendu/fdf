/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbendu <dbendu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/03 21:24:13 by dbendu            #+#    #+#             */
/*   Updated: 2019/12/16 21:06:07 by dbendu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void		set_colors(t_point *a, t_point *b)
{
	float gip;

	gip = sqrt(pow(a->x - b->x, 2) + pow(a->y - b->y, 2));
	a->red_shift = fabsf(a->red - b->red) / gip;
	a->green_shift = fabsf(a->green - b->green) / gip;
	a->blue_shift = fabsf(a->blue - b->blue) / gip;
	if (a->red > b->red)
		a->red_shift = -a->red_shift;
	if (a->green > b->green)
		a->green_shift = -a->green_shift;
	if (a->blue > b->blue)
		a->blue_shift = -a->blue_shift;
}

static void		brez_vert_gradient(t_wnd *wnd, t_point *a, t_point *b)
{
	const int	dx = b->x - a->x > 0 ? 1 : -1;
	const int	dy = b->y - a->y > 0 ? 1 : -1;
	const int	lenx = ft_abs(b->x - a->x);
	const int	leny = ft_abs(b->y - a->y);
	int			iters;
	int			d;

	set_colors(a, b);
	d = -leny;
	iters = ft_max(lenx, leny) + 1;
	while (iters--)
	{
		if (a->x >= 0 && a->y >= 0 && a->x <= MAX_X && a->y <= MAX_Y)
			*(t_uint32*)(wnd->img + a->y * wnd->size_line + a->x * wnd->bytes) =
				((int)a->red << 16) + ((int)a->green << 8) + a->blue;
		a->red += a->red_shift;
		a->green += a->green_shift;
		a->blue += a->blue_shift;
		a->y += dy;
		d += 2 * lenx;
		if (d > 0)
		{
			d -= 2 * leny;
			a->x += dx;
		}
	}
}

static void		brez_hor_gradiend(t_wnd *wnd, t_point *a, t_point *b)
{
	const int	dx = b->x - a->x > 0 ? 1 : -1;
	const int	dy = b->y - a->y > 0 ? 1 : -1;
	const int	lenx = ft_abs(b->x - a->x);
	const int	leny = ft_abs(b->y - a->y);
	int			iters;
	int			d;

	set_colors(a, b);
	d = -lenx;
	iters = ft_max(lenx, leny) + 1;
	while (iters--)
	{
		if (a->x >= 0 && a->y >= 0 && a->x <= MAX_X && a->y <= MAX_Y)
			*(t_uint32*)(wnd->img + a->y * wnd->size_line + a->x * wnd->bytes) =
				((int)a->red << 16) + ((int)a->green << 8) + a->blue;
		a->red += a->red_shift;
		a->green += a->green_shift;
		a->blue += a->blue_shift;
		a->x += dx;
		d += 2 * leny;
		if (d > 0)
		{
			d -= 2 * lenx;
			a->y += dy;
		}
	}
}

void			draw_line(t_wnd *wnd, t_point a, t_point b)
{
	int lenx;
	int leny;

	if ((a.x < 0 && b.x < 0) || (a.y < 0 && b.y < 0) ||
		(a.x > MAX_X && b.x > MAX_X) || (a.y > MAX_Y && b.y > MAX_Y))
		return ;
	lenx = ft_abs(b.x - a.x);
	leny = ft_abs(b.y - a.y);
	if (lenx > leny)
		brez_hor_gradiend(wnd, &a, &b);
	else
		brez_vert_gradient(wnd, &a, &b);
	return ;
}
