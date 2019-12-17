/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbendu <dbendu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/08 17:57:27 by user              #+#    #+#             */
/*   Updated: 2019/12/17 15:44:53 by dbendu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void		file_error(t_data ***map, const char *msg)
{
	vec_clear(map);
	error(2, msg, NULL, 0);
}

static void		get_color(const char **str, t_data *point,
							t_data ***map)
{
	++*str;
	if ((*str)[0] != '0' || (*str)[1] != 'x')
		file_error(map, "invalid syntax: [num],[\'0x\'_hex_]");
	*str += 2;
	point->color = hex_to_dec(*str);
	while (ft_ishex(**str))
		++*str;
	if (**str && !ft_isspace(**str))
		file_error(map, "invalid syntax: nums must been divided by spaces");
}

static void		parse_str(t_data ***map, const char *str)
{
	t_data point;

	while (*str)
	{
		while (ft_isspace(*str))
			++str;
		if (!*str)
			break;
		point.z = ft_atoi(str);
		if (*str == '+' || *str == '-')
			++str;
		if (!ft_isdigit(*str))
			file_error(map, "invalid syntax: nan");
		while (ft_isdigit(*str))
			++str;
		if (*str == ',')
			get_color(&str, &point, map);
		else
			point.color = __WHITE;
		vec_pushback(&(*map)[vec_rows(*map) - 1], &point);
	}
}

t_data			**get_data(const char *filename)
{
	int		fd;
	char	*str;
	t_data	**map;
	size_t	rows;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		error(2, "invalid file", NULL, 0);
	map = NULL;
	rows = 0;
	while (get_next_line(fd, &str) == 1)
	{
		map ? vec_addrow(&map, vec_size(map[0])) :
				(map = vec_init(1, 0, sizeof(t_data)));
		parse_str(&map, str);
		free(str);
		if (rows && vec_size(map[rows]) != vec_size(map[rows - 1]))
			file_error(&map, "invalid syntax: different len of strings");
		++rows;
	}
	close(fd);
	if (!map || !vec_size(map[0]))
		file_error(&map, "empty file");
	return (map);
}
