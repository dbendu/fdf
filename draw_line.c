/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbendu <dbendu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/03 21:24:13 by dbendu            #+#    #+#             */
/*   Updated: 2019/12/03 21:52:49 by dbendu           ###   ########.fr       */
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

static void		Brez_vert(t_wnd *wnd, t_point *a, t_point *b)
{
	const int	dx = b->x - a->x > 0 ? 1 : -1;
	const int	dy = b->y - a->y > 0 ? 1 : -1;
	const int	lenX = ft_abs(b->x - a->x);
	const int	lenY = ft_abs(b->y - a->y);
	int			iters;
	int			d;

	iters = ft_max(lenX, lenY) + 1;
	d = -lenY;
	while (iters--)
	{
		if (a->x >= 0 && a->y >= 0 && a->x <= MAX_X && a->y <= MAX_Y)
			*(uint32_t*)(wnd->img + a->y * wnd->size_line + a->x * wnd->bytes) =
				((int)a->red << 16) + ((int)a->green << 8) + a->blue;
		a->red += a->red_shift;
		a->green += a->green_shift;
		a->blue += a->blue_shift;
		a->y += dy;
		d += 2 * lenX;
		if (d > 0)
		{
			d -= 2 * lenY;
			a->x += dx;
		}
	}
}

static void		Brez_hor(t_wnd *wnd, t_point *a, t_point *b)
{
	const int	dx = b->x - a->x > 0 ? 1 : -1;
	const int	dy = b->y - a->y > 0 ? 1 : -1;
	const int	lenX = ft_abs(b->x - a->x);
	const int	lenY = ft_abs(b->y - a->y);
	int			iters;
	int			d;

	iters = ft_max(lenX, lenY) + 1;
	d = -lenX;
	while (iters--)
	{
		if (a->x >= 0 && a->y >= 0 && a->x <= MAX_X && a->y <= MAX_Y)
			*(uint32_t*)(wnd->img + a->y * wnd->size_line + a->x * wnd->bytes) =
				((int)a->red << 16) + ((int)a->green << 8) + a->blue;
		a->red += a->red_shift;
		a->green += a->green_shift;
		a->blue += a->blue_shift;
		a->x += dx;
		d += 2 * lenY;
		if (d > 0)
		{
			d -= 2 * lenX;
			a->y += dy;
		}
	}
}

void			draw_line(t_wnd *wnd, t_point a, t_point b)
{
	int lenX;
	int lenY;

	if ((a.x < 0 && b.x < 0) || (a.y < 0 && b.y < 0) ||
		(a.x > MAX_X && b.x > MAX_X) || (a.y > MAX_Y && b.y > MAX_Y))
		return ;
	set_colors(&a, &b);
	lenX = ft_abs(b.x - a.x);
	lenY = ft_abs(b.y - a.y);
	if (lenX > lenY)
		Brez_hor(wnd, &a, &b);
	else
		Brez_vert(wnd, &a, &b);
	return ;
}
