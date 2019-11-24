#include <math.h>
#include <inttypes.h>

#include "libft/includes/libft.h"
#include "minilibx/mlx.h"

#define WIDTH	1500
#define HEIGHT	1000

#define MAX_X	(WIDTH - 1)
#define MAX_Y	(HEIGHT - 1)

#define ESC		65307

#define MINUS	45
#define PLUS	61

#define SPACE	32

#define W		119
#define S		115
#define A		97
#define D		100

#define Q		113
#define E		101

#define UP		65362
#define DOWN	65364
#define LEFT	65361
#define RIGHT	65363

#define __white		16777215
// #define __purple	16711935
#define __purple	16711680

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
	int z_offset;

	int x_center;
	int y_center;
	int z_center;
}				t_wnd;

void draw_line(t_wnd *wnd, t_point *a, t_point *b, uint32_t color);
t_point **get_map(const char *file);
