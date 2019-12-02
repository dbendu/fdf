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
	double r_d = abs((((a.color >> 16) & 255) - ((b.color >> 16) & 255))) / gip;
	double g_d = abs((((a.color >> 8) & 255) - ((b.color >> 8) & 255))) / gip;
	double b_d = abs(((a.color & 255) - (b.color & 255))) / gip;
	if (((a.color >> 16) & 255) > ((b.color >> 16) & 255))
		r_d = -r_d;
	if (((a.color >> 8) & 255) > ((b.color >> 8) & 255))
		g_d = -g_d;
	if ((a.color & 255) > (b.color & 255))
		b_d = -b_d;

	iters = ft_max(lenX, lenY) + 1;
	d = -lenY;
	while (iters--)
	{
		*(uint32_t*)(wnd->img + a.y * wnd->size_line + a.x * wnd->bytes) = a.color;
		// a.color += (int)r_d << 16;
		// a.color += (int)g_d << 8;
		// a.color += (int)b_d;
		a.color += FLOAT_TO_INT(r_d) << 16;
		a.color += FLOAT_TO_INT(g_d) << 8;
		a.color += FLOAT_TO_INT(b_d);
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
	double r_d = abs((((a.color >> 16) & 255) - ((b.color >> 16) & 255))) / gip;
	double g_d = abs((((a.color >> 8) & 255) - ((b.color >> 8) & 255))) / gip;
	double b_d = abs(((a.color & 255) - (b.color & 255))) / gip;
	if (((a.color >> 16) & 255) > ((b.color >> 16) & 255))
		r_d = -r_d;
	if (((a.color >> 8) & 255) > ((b.color >> 8) & 255))
		g_d = -g_d;
	if ((a.color & 255) > (b.color & 255))
		b_d = -b_d;

	iters = ft_max(lenX, lenY) + 1;
	d = -lenX;
	while (iters--)
	{
		*(uint32_t*)(wnd->img + a.y * wnd->size_line + a.x * wnd->bytes) = a.color;
		a.color += FLOAT_TO_INT(r_d) << 16;
		a.color += FLOAT_TO_INT(g_d) << 8;
		a.color += FLOAT_TO_INT(b_d);
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

	// int code1 = code(a->x, a->y);
	// int code2 = code(b->x, b->y);
	// float dx = b->x - a->x;
	// float dy = b->y - a->y;
	// while (code1 | code2)
	// {
	// 	if (code1 & code2)
	// 		return ;
	// 	if (code1)
	// 	{
	// 		if (a->x < 0)
	// 		{
	// 			a->y += dy * (0 - a->x) / dx;
	// 			a->x = 0;
	// 		}
	// 		else if (a->x > 1500)
	// 		{
	// 			a->y += dy * (1500 - a->x) / dx;
	// 			a->x = 1500;
	// 		}
	// 		else if (a->y < 0)
	// 		{
	// 			a->x += dx * (0 - a->y) / dy;
	// 			a->y = 0;
	// 		}
	// 		else if (a->y > 1000)
	// 		{
	// 			a->x += dx * (1000 - a->y) / dy;
	// 			a->y = 1000;
	// 		}
	// 		code1 = code(a->x, a->y);
	// 	}
	// 	else
	// 	{
	// 		if (b->x < 0)
	// 		{
	// 			b->y += dy * (0 - b->x) / dx;
	// 			b->x = 0;
	// 		}
	// 		else if (b->x > 1500)
	// 		{
	// 			b->y += dy * (1500 - b->x) / dx;
	// 			b->x = 1500;
	// 		}
	// 		else if (b->y < 0)
	// 		{
	// 			b->x += dx * (0 - b->y) / dy;
	// 			b->y = 0;
	// 		}
	// 		else if (b->y > 1000)
	// 		{
	// 			b->x += dx * (1000 - b->y) / dy;
	// 			b->y = 1000;
	// 		}
	// 		code2 = code(b->x, b->y);
	// 	}

	// }

	lenX = ft_abs(b->x - a->x);
	lenY = ft_abs(b->y - a->y);
	if (lenX > lenY)
		Brez2(wnd, *a, *b);
	else
		Brez1(wnd, *a, *b);
	return ;
}
