#include <math.h>

#include "libft.h"
#include "mlx.h"


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

# define WHEEL_UP	5
# define WHEEL_DOWN	4

# define TAB	65289

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

# define WHEEL_UP	5
# define WHEEL_DOWN	4

# define TAB	48

#endif

# define MAX_X	(WIDTH - 1)
# define MAX_Y	(HEIGHT - 1)

# define __white		16777215
# define __red			16711680
# define __background	0x101010

typedef struct	s_point
{
	int			x;
	int			y;
	int			z;
	float		red;
	float		green;
	float		blue;
	float		red_shift;
	float		green_shift;
	float		blue_shift;
}				t_point;

typedef struct	s_angles
{
	double		x_angle;
	double		z_angle;
	double		y_angle;

	double		sin_x;
	double		sin_y;
	double		sin_z;
	double		cos_x;
	double		cos_z;
	double		cos_y;

	double		czcy;
	double		szcx;
	double		czsysx;
	double		szsx;
	double		czsycx;

	double		szcy;
	double		czcx;
	double		sxsysz;
	double		czsx;
	double		szsycx;

	double		cysx;
	double		cycx;
}				t_angles;

typedef struct	s_wnd
{
	void		*mlxptr;
	void		*wndptr;
	void		*imgptr;
	char		*img;
	t_point		**map;
	t_point 	**map_cp;
	t_angles	angles;

	int			bytes;
	int			size_line;
	int			endian;
	unsigned	cell;



	int x_offset;
	int y_offset;
	int z_offset;


	int x_center;
	int y_center;

	t_bool	is_mouse_active;
	int		mouse_x;
	int		mouse_y;

	int	rows;
	int	cols;

	

	t_bool show_menu;

	

}				t_wnd;

void		draw_line(t_wnd *wnd, t_point a, t_point b);
t_point		**get_map(const char *file);
void		draw_map(t_wnd *wnd);
int			key_press(int keycode, t_wnd *wnd);
void fdf_exit(t_wnd *wnd);
void shift_map(t_wnd *wnd, int x_, int y_);
void rotate(t_wnd *wnd);

int mouse_press(int button, int x, int y, t_wnd *wnd);
int mouse_release(int button, int x, int y, t_wnd *wnd);
int mouse_move(int x, int y, t_wnd *wnd);