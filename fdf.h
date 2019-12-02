#include <math.h>
#include <inttypes.h>

#include "libft/includes/libft.h"
#include "minilibx/mlx.h"


#ifdef __unix__

# define WIDTH	1800
# define HEIGHT	1000

# define ESC	65307

# define MINUS	45
# define PLUS	61

# define SPACE	32

# define W		119
# define S		115
# define A		97
# define D		100

# define Q		113
# define E		101

# define UP		65362
# define DOWN	65364
# define LEFT	65361
# define RIGHT	65363

# define I		105
# define O		111

#else

# define WIDTH	2500
# define HEIGHT	1300

# define ESC	53

# define MINUS	27
# define PLUS	24

# define SPACE	49

# define W		13
# define S		1
# define A		0
# define D		2

# define Q		12
# define E		14

# define UP		126
# define DOWN	125
# define LEFT	123
# define RIGHT	124

# define I		34
# define O		31

# define SHIFT	257
# define CTRL	256

# define WHEEL_UP	5
# define WHEEL_DOWN	4

#endif

#define MAX_X	(WIDTH - 1)
#define MAX_Y	(HEIGHT - 1)

#define __white		16777215
#define __red		16711680

typedef struct	s_point
{
	int x;
	int y;
	int z;
	float a_color;
	float g_color;
	float b_color;
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

	int z_shift;

	int x_center;
	int y_center;
	int z_center;

	t_bool	is_mouse_active;
	int		mouse_x;
	int		mouse_y;

	size_t rows;
	size_t cols;

	double sin_x;
	double sin_y;
	double sin_z;
	double cos_x;
	double cos_z;
	double cos_y;

}				t_wnd;

void		draw_line(t_wnd *wnd, t_point *a, t_point *b);
t_point		**get_map(const char *file);
void		print_map(t_wnd *wnd);