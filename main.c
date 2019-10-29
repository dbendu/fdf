#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define rows 30
#define cols 30

#define FLOAT_TO_INT(x) ((x)>=0?(int)((x)+0.5):(int)((x)-0.5))

int max(int a, int b)
{
	if (a > b)
		return (a);
	return (b);
}

void clear_map(char **map)
{
	memset(map[0], '.', rows * (cols + 1));
	for (size_t i = 0; i < rows; ++i)
		map[i][cols] = '\0';
}

void print_map(char **map)
{
	printf("    ");
	for (int i = 0; i < cols; ++i)
		printf("%3d", i);
	printf("\n");
	for (int i = 0; i < rows; ++i)
	{
		printf("%2d  ", i);
		for (int j = 0; j < cols; ++j)
			printf("%3c", map[i][j]);
		printf("\n");
	}
}

void Brez(char **map, int x1, int y1, int x2, int y2)
{
	int dx = x2 - x1 > 0 ? 1 : -1;
	int dy = y2 - y1 > 0 ? 1 : -1;
	int lenX = abs(x2 - x1);
	int lenY = abs(y2 - y1);
	int iters = max(lenX, lenY) + 1;

	if (lenX > lenY)
	{
		int d = -lenX;
		while (iters--)
		{
			map[x1][y1] = '#';
			x1 += dx;
			d += 2 * lenY;
			if (d > 0)
			{
				d -= 2 * lenY;
				y1 += dy;
			}
		}
	}
	else
	{
		int d = -lenY;
		while (iters--)
		{
			map[x1][y1] = '#';
			y1 += dy;
			d += 2 * lenX;
			if (d > 0)
			{
				d -= 2 * lenY;
				x1 += dx;
			}
		}
	}
}

int main(void)
{
	char **map;

	map = (char**)malloc(sizeof(char*) * rows);
	map[0] = (char*)malloc(rows * (cols + 1));
	for (size_t i = 1; i < rows; ++i)
		map[i] = map[i - 1] + cols + 1;

	clear_map(map);
	Brez(map, 1, 1, 10, 15);
	print_map(map);
	getchar();

	clear_map(map);
	Brez(map, 10, 15, 1, 1);
	print_map(map);
	getchar();

	clear_map(map);
	Brez(map, 1, 15, 10, 1);
	print_map(map);
	getchar();

	clear_map(map);
	Brez(map, 10, 1, 1, 15);
	print_map(map);





	free(map[0]);
	free(map);
	return (0);
}
