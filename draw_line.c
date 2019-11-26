#include "fdf.h"

void Brez1(t_wnd *wnd, t_point a, t_point b, uint32_t color)
{
	const int	dx = b.x - a.x > 0 ? 1 : -1;
	const int	dy = b.y - a.y > 0 ? 1 : -1;
	const int	lenX = ft_abs(b.x - a.x);
	const int	lenY = ft_abs(b.y - a.y);
	int			iters;
	int			d;

	iters = ft_max(lenX, lenY) + 1;
	d = -lenY;
	while (iters--)
	{
		*(uint32_t*)(wnd->img + (int)a.y * wnd->size_line + (int)a.x * wnd->bytes) = color;
		a.y += dy;
		d += 2 * lenX;
		if (d > 0)
		{
			d -= 2 * lenY;
			a.x += dx;
		}
	}
}

void Brez2(t_wnd *wnd, t_point a, t_point b, uint32_t color)
{
	const int	dx = b.x - a.x > 0 ? 1 : -1;
	const int	dy = b.y - a.y > 0 ? 1 : -1;
	const int	lenX = ft_abs(b.x - a.x);
	const int	lenY = ft_abs(b.y - a.y);
	int			iters;
	int			d;

	iters = ft_max(lenX, lenY) + 1;
	d = -lenX;
	while (iters--)
	{
		*(uint32_t*)(wnd->img + (int)a.y * wnd->size_line + (int)a.x * wnd->bytes) = color;
		a.x += dx;
		d += 2 * lenY;
		if (d > 0)
		{
			d -= 2 * lenX;
			a.y += dy;
		}
	}
}

int code(float x, float y)
{
	return ((x < 0) << 3 | (x > MAX_X) << 2 | (y < 0) << 1 | (y > MAX_Y));
}

void draw_line(t_wnd *wnd, t_point *a, t_point *b, uint32_t color)
{
	int lenX;
	int lenY;

	float dx = b->x - a->x;
	float dy = b->y - a->y;
	while (code(a->x, a->y) | code(b->x, b->y))
	{
		if (code(a->x, b->x) & code(b->x, b->y))
			return ;
		if (code(a->x, a->y))
		{
			if (a->x < 0)
			{
				a->y += dy * (0 - a->x) / dx;
				a->x = 0;
			}
			else if (a->x > MAX_X)
			{
				a->y += dy * (MAX_X - a->x) / dx;
				a->x = MAX_X;
			}
			else if (a->y < 0)
			{
				a->x += dx * (0 - a->y) / dy;
				// a->x += (float)a->y / (a->y - b->y) * (b->x - a->x);
				a->y = 0;
			}
			else if (a->y > MAX_Y)
			{
				a->x += dx * (MAX_Y - a->y) / dy;
				a->y = MAX_Y;
			}
		}
		else
		{
			if (b->x < 0)
			{
				b->y += dy * (0 - b->x) / dx;
				b->x = 0;
			}
			else if (b->x > MAX_X)
			{
				b->y += dy * (MAX_X - b->x) / dx;
				b->x = MAX_X;
			}
			else if (b->y < 0)
			{
				b->x += dx * (0 - b->y) / dy;
				b->y = 0;
			}
			else if (b->y > MAX_Y)
			{
				b->x += dx * (MAX_Y - b->y) / dy;
				b->y = MAX_Y;
			}
		}
	}

	lenX = ft_abs(b->x - a->x);
	lenY = ft_abs(b->y - a->y);
	if (lenX > lenY)
		Brez2(wnd, *a, *b, color);
	else
		Brez1(wnd, *a, *b, color);
	return ;
}
