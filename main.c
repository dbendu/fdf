/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbendu <dbendu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/03 21:20:42 by dbendu            #+#    #+#             */
/*   Updated: 2019/12/16 21:02:52 by dbendu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "fdf.h"

void	usage(void)
{
	write(1, "\e[38;5;001mUsage\e[0m: ./fdf file_name\n", 38);
	ft_exit(0);
}

void	fdf_exit(t_wnd *wnd)
{
	vec_clear(&wnd->map);
	vec_clear(&wnd->map_cp);
	mlx_destroy_image(wnd->mlxptr, wnd->imgptr);
	mlx_destroy_window(wnd->mlxptr, wnd->wndptr);
	exit(0);
}

void	get_mlx(t_wnd *wnd)
{
	wnd->mlxptr = mlx_init();
	if (!wnd->mlxptr)
		error(2, "cant create mlx", "get_mlx", 0);
	wnd->wndptr = mlx_new_window(wnd->mlxptr, WIDTH, HEIGHT, "fdf");
	if (!wnd->wndptr)
		error(2, "cant create wnd", "get_mlx", 0);
	wnd->imgptr = mlx_new_image(wnd->mlxptr, WIDTH, HEIGHT);
	if (!wnd->imgptr)
	{
		mlx_destroy_window(wnd->mlxptr, wnd->wndptr);
		error(2, "cant create img", "get_mlx", 0);
	}
	wnd->img = mlx_get_data_addr(wnd->imgptr, &wnd->bytes, &wnd->size_line,
								&wnd->endian);
}

t_wnd	wnd_init(const char **argv)
{
	t_wnd wnd;

	ft_memset(&wnd, 0, sizeof(t_wnd));
	wnd.map = get_map(argv[1]);
	wnd.map_cp = vec_cp(wnd.map);
	get_mlx(&wnd);
	wnd.bytes /= 8;
	wnd.cell = 5;
	wnd.show_menu = TRUE;
	wnd.show_info = TRUE;
	wnd.rows = (int)vec_rows(wnd.map);
	wnd.cols = (int)vec_size(wnd.map[0]);
	if (wnd.rows > 40 || (wnd.rows > 20 && wnd.cols > 100))
		wnd.threads = TRUE;
	wnd.x_offset = WIDTH / 2 - vec_size(wnd.map[0]) * wnd.cell / 2;
	wnd.y_offset = HEIGHT / 2 - vec_rows(wnd.map) * wnd.cell / 2;
	rotate(&wnd);
	draw_map(&wnd);
	return (wnd);
}

int		main(int argc, const char **argv)
{
	t_wnd wnd;

	if (argc != 2)
	{
		usage();
		return (0);
	}
	wnd = wnd_init(argv);
	mlx_hook(wnd.wndptr, 2, 1L << 0, key_press, &wnd);
	mlx_hook(wnd.wndptr, 4, 1L << 2, mouse_press, &wnd);
	mlx_hook(wnd.wndptr, 5, 1L << 3, mouse_release, &wnd);
	mlx_hook(wnd.wndptr, 6, 1L << 13, mouse_move, &wnd);
	mlx_loop(wnd.mlxptr);
	return (0);
}
