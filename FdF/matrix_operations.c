#include "fdf.h"

void rotate_z(basic *mlb)
{
	int i;
	int j;
	long double angle;
	long double new_x;
	long double new_y;

	i = 0;
	j = 0;
	angle = 10 * M_PI / 180.0;
	while (mlb->map[i] != 0)
	{
		while (j < mlb->nr_p_line)
		{
			new_x = cos(angle) * mlb->map[i][j].x - sin(angle) * mlb->map[i][j].y;
			new_y = sin(angle) * mlb->map[i][j].x + cos(angle) * mlb->map[i][j].y;
			mlb->map[i][j].x = new_x;
			mlb->map[i][j].y = new_y;
			j++;
		}
		j = 0;
		i++;
	}
}

void rotate_y(basic *mlb)
{
	int i;
	int j;
	long double angle;
	long double new_x;
	long double new_z;

	i = 0;
	j = 0;
	angle = 10 * M_PI / 180.0;
	while (mlb->map[i] != 0)
	{
		while (j < mlb->nr_p_line)
		{
			new_x = cos(angle) * mlb->map[i][j].x + sin(angle) * mlb->map[i][j].z;
			new_z = -sin(angle) * mlb->map[i][j].x + cos(angle) * mlb->map[i][j].z;
			mlb->map[i][j].x = new_x;
			mlb->map[i][j].z = new_z;
			j++;
		}
		j = 0;
		i++;
	}
}

void rotate_x(basic *mlb)
{
	int i;
	int j;
	long double angle;
	long double new_y;
	long double new_z;

	i = 0;
	j = 0;
	angle = 10 * M_PI / 180.0;
	while (mlb->map[i] != 0)
	{
		while (j < mlb->nr_p_line)
		{
			new_y = cos(angle) * mlb->map[i][j].y - sin(angle) * mlb->map[i][j].z;
			new_z = sin(angle) * mlb->map[i][j].y + cos(angle) * mlb->map[i][j].z;
			mlb->map[i][j].y = new_y;
			mlb->map[i][j].z = new_z;
			j++;
		}
		j = 0;
		i++;
	}
}

matrix **convert_to_matrix(long double **map, int x, int y)
{
	matrix **map_matrix;
	int i = 0;
	int j = 0;

	map_matrix = malloc(y * sizeof(matrix *));
	while (i < y - 1)
	{
		map_matrix[i] = malloc(x * sizeof(matrix));
		while (j < x)
		{
			map_matrix[i][j].x = (long double)(-(x + 1) / 2 + j + 1);
			map_matrix[i][j].y = (long double)(y / 2 - i - 1);
			map_matrix[i][j].z = map[i][j];
			j++;
		}
		j = 0;
		i++;
	}
	map_matrix[i] = 0;
	return map_matrix;
}
