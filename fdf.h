#include <math.h>

#include "libft/includes/libft.h"
#include "minilibx/mlx.h"

#define W	1200
#define H	1100

#define __white	16777215

typedef struct	s_point
{
	int x;
	int y;
	int z;
	int color;
}				t_point;

typedef struct	s_wnd
{
	void	*mlxptr;
	void	*wndptr;
	void	*imgptr;
	char	*img;
	t_point	**map;

	int		bytes_per_pixel;
	int		size_line;
	int		endian;

	// double	x_angle;
}				t_wnd;

void draw_line(t_wnd *wnd, const t_point *a, const t_point *b);
t_point **get_map(const char *file);
