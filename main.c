/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbendu <dbendu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/03 21:20:42 by dbendu            #+#    #+#             */
/*   Updated: 2019/12/04 03:54:25 by dbendu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

t_wnd	wnd_init(const char **argv)
{
	t_wnd wnd;

	ft_memset(&wnd, 0, sizeof(t_wnd));
	wnd.mlxptr = mlx_init();
	wnd.wndptr = mlx_new_window(wnd.mlxptr, WIDTH, HEIGHT, "fdf");
	wnd.imgptr = mlx_new_image(wnd.mlxptr, WIDTH, HEIGHT);
	wnd.img = mlx_get_data_addr(wnd.imgptr, &wnd.bytes, &wnd.size_line,
								&wnd.endian);
	wnd.bytes /= 8;
	wnd.cell = 5
	;
	wnd.show_menu = 1;
	wnd.map = get_map(argv[1]);
	wnd.map_cp = vec_cp(wnd.map);
	wnd.rows = (int)vec_rows(wnd.map);
	wnd.cols = (int)vec_size(wnd.map[0]);
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
