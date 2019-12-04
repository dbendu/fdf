/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbendu <dbendu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/03 21:24:13 by dbendu            #+#    #+#             */
/*   Updated: 2019/12/03 22:13:30 by dbendu           ###   ########.fr       */
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

static void		brez_vert(t_wnd *wnd, t_point *a, t_point *b, int iters)
{
	const int	dx = b->x - a->x > 0 ? 1 : -1;
	const int	dy = b->y - a->y > 0 ? 1 : -1;
	const int	lenx = ft_abs(b->x - a->x);
	const int	leny = ft_abs(b->y - a->y);
	int			d;

	iters = ft_max(lenx, leny) + 1;
	d = -leny;
	while (iters--)
	{
		if (a->x >= 0 && a->y >= 0 && a->x <= MAX_X && a->y <= MAX_Y)
			*(uint32_t*)(wnd->img + a->y * wnd->size_line + a->x * wnd->bytes) =
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

static void		brez_hor(t_wnd *wnd, t_point *a, t_point *b, int iters)
{
	const int	dx = b->x - a->x > 0 ? 1 : -1;
	const int	dy = b->y - a->y > 0 ? 1 : -1;
	const int	lenx = ft_abs(b->x - a->x);
	const int	leny = ft_abs(b->y - a->y);
	int			d;

	iters = ft_max(lenx, leny) + 1;
	d = -lenx;
	while (iters--)
	{
		if (a->x >= 0 && a->y >= 0 && a->x <= MAX_X && a->y <= MAX_Y)
			*(uint32_t*)(wnd->img + a->y * wnd->size_line + a->x * wnd->bytes) =
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
	set_colors(&a, &b);
	lenx = ft_abs(b.x - a.x);
	leny = ft_abs(b.y - a.y);
	if (lenx > leny)
		brez_hor(wnd, &a, &b, 0);
	else
		brez_vert(wnd, &a, &b, 0);
	return ;
}
