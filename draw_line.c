#include <stdio.h>
#include <math.h>

#include "fdf.h"

#define FLOAT_TO_INT(x) ((x)>=0?(int)((x)+0.5):(int)((x)-0.5))

void Brez1(t_wnd *wnd, t_point a, t_point b)
{
	const int	dx = b.x - a.x > 0 ? 1 : -1;
	const int	dy = b.y - a.y > 0 ? 1 : -1;
	const int	lenX = ft_abs(b.x - a.x);
	const int	lenY = ft_abs(b.y - a.y);
	int			iters;
	int			d;

	double gip = sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2));
	double r_d = fabsf(a.a_color - b.a_color) / gip;
	double g_d = fabsf(a.g_color - b.g_color) / gip;
	double b_d = fabsf(a.b_color - b.b_color) / gip;
	if (a.a_color > b.a_color)
		r_d = -r_d;
	if (a.g_color > b.g_color)
		g_d = -g_d;
	if (a.b_color > b.b_color)
		b_d = -b_d;

	iters = ft_max(lenX, lenY) + 1;
	d = -lenY;
	while (iters--)
	{
		int color = ((int)a.a_color << 16) + ((int)a.g_color << 8) + a.b_color;
		if (a.x >= 0 && a.y >= 0 && a.x <= MAX_X && a.y <= MAX_Y)
			*(uint32_t*)(wnd->img + a.y * wnd->size_line + a.x * wnd->bytes) = color;
		a.a_color += r_d;
		a.g_color += g_d;
		a.b_color += b_d;
		a.y += dy;
		d += 2 * lenX;
		if (d > 0)
		{
			d -= 2 * lenY;
			a.x += dx;
		}
	}
}

void Brez2(t_wnd *wnd, t_point a, t_point b)
{
	const int	dx = b.x - a.x > 0 ? 1 : -1;
	const int	dy = b.y - a.y > 0 ? 1 : -1;
	const int	lenX = ft_abs(b.x - a.x);
	const int	lenY = ft_abs(b.y - a.y);
	int			iters;
	int			d;

	double gip = sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2));
	double r_d = fabsf(a.a_color - b.a_color) / gip;
	double g_d = fabsf(a.g_color - b.g_color) / gip;
	double b_d = fabsf(a.b_color - b.b_color) / gip;
	if (a.a_color > b.a_color)
		r_d = -r_d;
	if (a.g_color > b.g_color)
		g_d = -g_d;
	if (a.b_color > b.b_color)
		b_d = -b_d;

	iters = ft_max(lenX, lenY) + 1;
	d = -lenX;
	while (iters--)
	{
		int color = ((int)a.a_color << 16) + ((int)a.g_color << 8) + a.b_color;
		if (a.x >= 0 && a.y >= 0 && a.x <= MAX_X && a.y <= MAX_Y)
			*(uint32_t*)(wnd->img + a.y * wnd->size_line + a.x * wnd->bytes) = color;
		a.a_color += r_d;
		a.g_color += g_d;
		a.b_color += b_d;
		// a.color += (int)r_d << 16;
		// a.color += (int)g_d << 8;
		// a.color += (int)b_d;

		a.x += dx;
		d += 2 * lenY;
		if (d > 0)
		{
			d -= 2 * lenX;
			a.y += dy;
		}
	}
}

int code(int x, int y)
{
	return ((x < 0) << 3 | (x > MAX_X) << 2 | (y < 0) << 1 | (y > MAX_Y));
}

void draw_line(t_wnd *wnd, t_point *a, t_point *b)
{
	int lenX;
	int lenY;

	if ((a->x < 0 && b->x < 0) || (a->y < 0 && b->y < 0) ||
		(a->x > MAX_X && b->x > MAX_X) || (a->y > MAX_Y && b->y > MAX_Y))
		return ;

	lenX = ft_abs(b->x - a->x);
	lenY = ft_abs(b->y - a->y);
	if (lenX > lenY)
		Brez2(wnd, *a, *b);
	else
		Brez1(wnd, *a, *b);
	return ;
}
