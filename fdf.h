#include <math.h>
#include <inttypes.h>

#include "libft/includes/libft.h"
#include "minilibx/mlx.h"

#define W	1500
#define H	1000

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
	t_point **map_cp;

	int		bytes;
	int		size_line;
	int		endian;
	unsigned	cell;
	double	x_angle;
	double	z_angle;
	double	y_angle;

	int x_offset;
	int y_offset;
}				t_wnd;

void draw_line(t_wnd *wnd, const t_point *a, const t_point *b, uint32_t color);
t_point **get_map(const char *file);
