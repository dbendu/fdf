/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbendu <dbendu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/03 23:35:38 by dbendu            #+#    #+#             */
/*   Updated: 2019/12/04 04:04:52 by dbendu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_bool			is_num(const char *str, const char *str_beg)
{
	size_t i;

	if (ft_isdigit(*str))
		return (TRUE);
	if ((*str == '+' || *str == '-') &&
		ft_isdigit(str[1]) &&
		(str == str_beg || ft_isspace(str[-1])))
		return (TRUE);
	if (*str == ',' && ft_strlen(str) > 3 &&
		str[1] == '0' && str[2] == 'x')
	{
		i = 3;
		while (!ft_isspace(str[i]))
		{
			if (!ft_ishex(*str))
				error(2, "invalid syntax", NULL, 0);
			++i;
		}
		return (TRUE);
	}
	error(2, "invalid syntax", NULL, 0);
	return (1);
}

t_bool			is_str_valid(const char *str)
{
	const char *iter;
	__int128_t value;

	iter = str;
	while (*iter)
	{
		while (ft_isspace(*iter))
			++iter;
		if (*iter && !is_num(iter, str))
			error(2, "invalid syntax", NULL, 0);
		if ((value = ft_atoi(iter)) > MAX_INT || value < MIN_INT)
			error(2, "values must been in range of int32", NULL, 0);
		if (*iter == '-' || *iter == '+')
			++iter;
		while (ft_isdigit(*iter))
			++iter;
		if (*iter == ',' && ft_strlen(iter) > 3 &&
			iter[1] == '0' && iter[2] == 'x' && ft_ishex(iter[3]))
		{
			iter += 3;
			while (ft_ishex(*iter))
				++iter;
		}
	}
	return (TRUE);
}

static void		get_color(t_point *point, const char **str)
{
	int color;

	if (**str == ',')
	{
		*str += 3;
		color = hex_to_dec(*str);
		point->red = (color >> 16) & 255;
		point->green = (color >> 8) & 255;
		point->blue = color & 255;
		while (ft_ishex(**str))
			++(*str);
	}
	else
	{
		point->red = 255;
		point->green = 255;
		point->blue = 255;
	}
}

void			parse_str(t_point ***map, const char *str)
{
	t_point		point;

	*map ? vec_addrow(map) :
			(*map = vec_init(1, 0, sizeof(t_point)));
	while (*str)
	{
		while (ft_isspace(*str))
			++str;
		if (!*str)
			break ;
		point.z = ft_atoi(str);
		if (*str == '-' || *str == '+')
			++str;
		while (ft_isdigit(*str))
			++str;
		get_color(&point, &str);
		vec_pushback(&((*map)[vec_rows(*map) - 1]), &point);
	}
}

t_point			**get_map(const char *file)
{
	t_point	**map;
	int		fd;
	char	*str;
	size_t rows;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		error(2, "invalid file", NULL, 0);
	rows = 0;
	map = NULL;
	while (get_next_line(fd, &str) == 1)
	{
		if (is_str_valid(str))
			parse_str(&map, str);
		else
			error(2, "Invalid map: invalid str", NULL, 0);
		if (rows && vec_size(map[rows]) != vec_size(map[rows - 1]))
			error(2, "Invalid map: different len of strings", NULL, 0);
		ft_free(str);
		++rows;
	}
	if (!map || !vec_size(map[0]))
		error(1, "Empty map", NULL, 0);
	return (map);
}
