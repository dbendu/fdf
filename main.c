/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbendu <dbendu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/03 21:20:42 by dbendu            #+#    #+#             */
/*   Updated: 2019/12/19 16:44:58 by dbendu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "fdf.h"

# define MAX_SOURCE_SIZE 10000

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

t_point	**map_init(const t_data **data)
{
	t_point	**map;
	size_t	rows;
	size_t	cols;
	t_point	point;

	rows = vec_rows(data);
	cols = vec_size(data[0]);
	map = vec_init(rows, cols, sizeof(t_point));
	for (size_t row = 0; row < rows; ++row)
	{
		for (size_t col = 0; col < cols; ++col)
		{
			point.red = (data[row][col].color >> 16) & 255;
			point.green = (data[row][col].color >> 8) & 255;
			point.blue = data[row][col].color & 255;
			vec_pushback(&(map[row]), &point);
		}
	}
	return (map);
}

int		anim(t_wnd *wnd)
{
	static int i = 4;

	if (wnd->is_anim == FALSE)
		return (1);

	if (wnd->shift_to == UP)
		shift_map(wnd, 0, -i * 10);
	else if (wnd->shift_to == LEFT)
		shift_map(wnd, -i * 10, 0);
	else if (wnd->shift_to == DOWN)
		shift_map(wnd, 0, i * 10);
	else if (wnd->shift_to == RIGHT)
		shift_map(wnd, i * 10, 0);
	draw_map(wnd);
	if (i == 1)
	{
		i = 4;
		wnd->is_anim = FALSE;
	}
	else
		--i;
	return (1);
}

t_wnd	wnd_init(const char **argv)
{
	t_wnd wnd;

	ft_memset(&wnd, 0, sizeof(t_wnd));
	wnd.map = get_data(argv[1]);
	wnd.map_cp = map_init((const t_data**)wnd.map);
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




typedef struct		s_aaaaa
{
	int		a;
	int		b;
	float	c;
}					t_aaaaa;





// int main(void)
int		main(int argc, const char **argv)
{
	t_wnd wnd;

	if (argc != 2)
	{
		usage();
		return (0);
	}
	wnd = wnd_init(argv);

	// cl_int				ret;
	// cl_platform_id		platform_id;
	// cl_uint				ret_num_platforms;
	// cl_device_id		device_id;
	// cl_uint				ret_num_devices;
	// cl_context			context;
	// cl_command_queue	command_queue;

	// ret = clGetPlatformIDs(1, &platform_id, &ret_num_platforms);
	// if (ret)
	// 	error(2, "AAAA", "AAA", 0);

	// /* получить доступные устройства */
	// ret = clGetDeviceIDs(platform_id, CL_DEVICE_TYPE_GPU, 1, &device_id, &ret_num_devices);
	// if (ret)
	// 	error(2, "AAAA", "AAA", 0);

	// /* создать контекст */
	// context = clCreateContext(NULL, 1, &device_id, NULL, NULL, &ret);
	// if (ret)
	// 	error(2, "AAAA", "AAA", 0);

	// /* создаем команду */
	// command_queue = clCreateCommandQueue(context, device_id, 0, &ret);
	// if (ret)
	// 	error(2, "AAAA", "AAA", 0);



	// cl_program program = NULL;
	// cl_kernel kernel = NULL;

	// FILE *fp;
	// const char fileName[] = "./test.cl";
	// size_t source_size;
	// char *source_str;

	// fp = fopen(fileName, "r");
	// if (!fp) {
	// 	fprintf(stderr, "Failed to load kernel.\n");
	// 	exit(1);
	// }
	// source_str = (char *)malloc(MAX_SOURCE_SIZE);
	// source_size = fread(source_str, 1, MAX_SOURCE_SIZE, fp);
	// fclose(fp);


	// /* создать бинарник из кода программы */
	// program = clCreateProgramWithSource(context, 1, (const char **)&source_str, (const size_t *)&source_size, &ret);
	// if (ret)
	// 	error(2, "AAAA", "AAA", 0);

	// /* скомпилировать программу */
	// ret = clBuildProgram(program, 1, &device_id, NULL, NULL, NULL);
	// if (ret)
	// 	error(2, "AAAA", "AAA", 0);

	// /* создать кернел */
	// kernel = clCreateKernel(program, "test", &ret);
	// if (ret)
	// 	error(2, "AAAA", "AAA", 0);




	// cl_mem memobj = NULL;
	// int memLenth = 100;
	// cl_int mem[memLenth];
	// // cl_int *mem = calloc(memLenth, sizeof(cl_int));

	// for (int i = 0; i < 100; ++i)
	// 	printf("%d\t", mem[i]);
	// printf("\n\n\n");

	// /* создать буфер */
	// memobj = clCreateBuffer(context, CL_MEM_READ_WRITE, memLenth * sizeof(cl_int), NULL, &ret);
	// if (ret)
	// 	error(2, "AAAA", "AAA", 0);

	// /* записать данные в буфер */
	// ret = clEnqueueWriteBuffer(command_queue, memobj, CL_TRUE, 0, memLenth * sizeof(cl_int), mem, 0, NULL, NULL);
	// if (ret)
	// 	error(2, "AAAA", "AAA", 0);

	// /* устанавливаем параметр */
	// ret = clSetKernelArg(kernel, 0, sizeof(cl_mem), (void *)&memobj);
	// if (ret)
	// 	error(2, "AAAA", "AAA", 0);



	// size_t global_work_size[1] = { 100 };

	// /* выполнить кернел */
	// ret = clEnqueueNDRangeKernel(command_queue, kernel, 1, NULL, global_work_size, NULL, 0, NULL, NULL);
	// if (ret)
	// 	error(2, "AAAA", "AAA", 0);

	// /* считать данные из буфера */
	// ret = clEnqueueReadBuffer(command_queue, memobj, CL_TRUE, 0, memLenth * sizeof(cl_int), mem, 0, NULL, NULL);
	// if (ret)
	// 	error(2, "AAAA", "AAA", 0);





	mlx_hook(wnd.wndptr, 2, 1L << 0, key_press, &wnd);
	mlx_hook(wnd.wndptr, 4, 1L << 2, mouse_press, &wnd);
	mlx_hook(wnd.wndptr, 5, 1L << 3, mouse_release, &wnd);
	mlx_hook(wnd.wndptr, 6, 1L << 13, mouse_move, &wnd);
	mlx_loop_hook(wnd.mlxptr, anim, &wnd);
	mlx_loop(wnd.mlxptr);
	return (0);
}
