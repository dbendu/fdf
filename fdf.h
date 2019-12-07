/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/04 01:34:25 by dbendu            #+#    #+#             */
/*   Updated: 2019/12/07 22:00:58 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <math.h>
# include <pthread.h>

# include "libft.h"
# include "mlx.h"

# ifdef __unix__

#  define WIDTH				1800
#  define HEIGHT			1000

# define MAX_X			(WIDTH - 1)
# define MAX_Y			(HEIGHT - 1)

#  define ESC			65307

#  define MINUS			45
#  define PLUS			61

#  define SPACE			32

#  define W				119
#  define S				115
#  define A				97
#  define D				100

#  define Q				113
#  define E				101

#  define UP			65362
#  define DOWN			65364
#  define LEFT			65361
#  define RIGHT			65363

#  define I				105

#  define WHEEL_UP		5
#  define WHEEL_DOWN	4

#  define LEFT_BUTTON	1
#  define RIGHT_BUTTON	3

#  define LESS			44
#  define MORE			46

#  define TAB			65289

# else

#  define WIDTH			2500
#  define HEIGHT		1350

#  define ESC			53

#  define MINUS			27
#  define PLUS			24

#  define SPACE			49

#  define W				13
#  define S				1
#  define A				0
#  define D				2

#  define Q				12
#  define E				14

#  define UP			126
#  define DOWN			125
#  define LEFT			123
#  define RIGHT			124

#  define I				34

#  define WHEEL_UP		5
#  define WHEEL_DOWN	4

#  define LEFT_BUTTON	1
#  define RIGHT_BUTTON	2

#  define LESS
#  define MORE

#  define TAB			48

# endif

# define __WHITE		16777215
# define __BLACK		0

typedef struct	s_point
{
	t_int32		x;
	t_int32		y;
	t_int32		z;
	float		red;
	float		green;
	float		blue;
	float		red_shift;
	float		green_shift;
	float		blue_shift;
}				t_point;

typedef struct	s_angles
{
	t_int16	x_angle;
	t_int16	z_angle;
	t_int16	y_angle;

	double		sin_x;
	double		sin_y;
	double		sin_z;
	double		cos_x;
	double		cos_z;
	double		cos_y;

	double		x_x;
	double		x_y;
	double		x_z;
	double		y_x;
	double		y_y;
	double		y_z;
	double		z_x;
	double		z_y;
	double		z_z;

}				t_angles;

typedef struct	s_mouse
{
	t_bool		is_left_button_active;
	t_bool		is_right_button_active;
	int32_t		x;
	int32_t		y;
}				t_mouse;

typedef struct	s_wnd
{
	void		*mlxptr;
	void		*wndptr;
	void		*imgptr;
	char		*img;
	t_point		**map;
	t_point		**map_cp;

	t_angles	angles;
	t_mouse		mouse;

	int32_t		rows;
	int32_t		cols;

	int32_t		bytes;
	int32_t		size_line;
	int32_t		endian;
	unsigned	cell;

	int32_t		x_offset;
	int32_t		y_offset;

	t_bool		show_menu;
	t_bool		show_info;

	t_int32		bkg_color;
	t_int32		fill_color;
}				t_wnd;

typedef struct	s_threads
{
	t_wnd		*wnd;
	int			y;
	int			x;
	int			y_end;
}				t_threads;

t_point			**get_map(const char *file);

void			draw_line(t_wnd *wnd, t_point a, t_point b);
void			draw_map(t_wnd *wnd);

void			shift_map(t_wnd *wnd, int32_t x_, int32_t y_);
void			rotate(t_wnd *wnd);

int32_t			key_press(int keycode, t_wnd *wnd);
int32_t			mouse_press(int32_t button, int32_t x, int32_t y, t_wnd *wnd);
int32_t			mouse_release(int32_t button, int32_t x, int32_t y, t_wnd *wnd);
int32_t			mouse_move(int32_t x, int32_t y, t_wnd *wnd);

void			*rotate_thread1(void *param);
void			*rotate_thread2(void *param);
void			*rotate_thread3(void *param);
void			*rotate_thread4(void *param);

void			fdf_exit(t_wnd *wnd);

#endif
