#include "fdf.h"

bool is_num(const char *str, const char *str_beg)
{
	size_t i;

	if (ft_isdigit(*str))
		return (true);
	if ((*str == '+' || *str == '-') &&
		ft_isdigit(str[1]) &&
		(str == str_beg || ft_isspace(str[-1])))
		return (true);
	if (*str == ',' && ft_strlen(str) > 3 &&
		str[1] == '0' && str[2] == 'x')
	{
		i = 3;
		while (!ft_isspace(str[i]))
		{
			if (!ft_ishex(*str))
				return (false);
			++i;
		}
		return (true);
	}
	return (false);
}

bool is_str_valid(const char *str)
{
	const char *iter;
	__int128_t value;

	iter = str;
	while (*iter)
	{
		while (ft_isspace(*iter))
			++iter;
		if (is_num(iter, str))
		{
			if ((value = ft_atoi(iter)) > MAX_INT || value < MIN_INT)
				return (false);
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
		else if (*iter)
			return (false);
	}
	return (true);
}

void parse_str(t_point ***map, const char *str)
{
	t_point			point;

	*map ? vec_addrow(map) : (*map = vec_init(1, 0, sizeof(t_point)));
	point.x = *map ? vec_rows(*map) : 0;
	point.y = 0;
	while (*str)
	{
		while (ft_isspace(*str))
			++str;
		if (!*str)
			break;
		point.z = ft_atoi(str);
		while (ft_isdigit(*str))
			++str;
		point.color = __white;		// white (?)
		if (*str == ',')
		{
			str += 3;
			point.color = hex_to_dec(str);
			while (ft_ishex(*str))
				++str;
		}
		vec_pushback(&((*map)[vec_rows(*map) - 1]), &point);
		++point.y;
	}
}

t_point **get_map(const char *file)
{
	t_point **map;
	int fd;
	char *str;
	int rows;

	fd = open(file, O_RDONLY);
	map = NULL;
	rows = 0;
	while (get_next_line(fd, &str) == 1)
	{
		if (is_str_valid(str))
			parse_str(&map, str);
		else
		{
			vec_clear(&map);
			error(2, "Invalid map", 0);
		}
		if (rows && vec_size(map[rows]) != vec_size(map[rows - 1]))
		{
			vec_clear(&map);
			error(2, "Invalid map", 0);
		}
		++rows;
		free(str);
	}
	if (!map || !vec_size(map[0]))
	{
		vec_clear(&map);
		error(1, "Empty map", 0);
	}
	return (map);
}
