#include "fdf.h"

void Brez1(t_wnd *wnd, t_point a, t_point b)
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
		*(int*)(wnd->img + a.x * wnd->size_line + b.x * wnd->bytes_per_pixel) = __white;
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

	iters = ft_max(lenX, lenY) + 1;
	d = -lenX;
	while (iters--)
	{
		*(int*)(wnd->img + a.x * wnd->size_line + b.x * wnd->bytes_per_pixel) = __white;
		a.x += dx;
		d += 2 * lenY;
		if (d > 0)
		{
			d -= 2 * lenX;
			a.y += dy;
		}
	}
}

void draw_line(t_wnd *wnd, const t_point *a, const t_point *b)
{
	int lenX;
	int lenY;

	lenX = ft_abs(b->x - a->x);
	lenY = ft_abs(b->y - a->y);
	if (lenX > lenY)
		Brez2(wnd, *a, *b);
	else
		Brez1(wnd, *a, *b);
	return ;
}
