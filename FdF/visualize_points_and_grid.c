#include "fdf.h"

int check_point(basic *mlb)
{
	int i = 0;
	int j = 0;

	while (i < mlb->nr_line - 1)
	{
		while (j < mlb->nr_p_line)
		{
			if (fabsl(mlb->xy[1] - (mlb->map)[i][j].y) < 0.1 && fabsl(mlb->xy[0] - (mlb->map)[i][j].x) < 0.1)
				return 0;
			j++;
		}
		j = 0;
		i++;
	}

	return 1;
}

// same for gradients

int gradients(basic *mlb, char c, int i, int j)
{
	long double dx1;
	long double dx2;
	long double dy1;
	long double dy2;

	dx1 = mlb->xy[0] - mlb->map[i][j].x;
	dx2 = mlb->xy[0] - mlb->map[i + 1][j].x;
	dy1 = mlb->xy[1] - mlb->map[i][j].y;
	dy2 = mlb->xy[1] - mlb->map[i + 1][j].y;
	if (c == 'i')
		if (fabsl(dx1 * dy2 - dx2 * dy1) > 0.02)
			return 1;
	dx2 = mlb->xy[0] - mlb->map[i][j + 1].x;
	dy2 = mlb->xy[1] - mlb->map[i][j + 1].y;
	if (c == 'j')
		if (fabsl(dx1 * dy2 - dx2 * dy1) > 0.02)
			return 1;
	return 0;
}

// check is between should quit earlier because more points not inbetween the inbetween

int check_is_between(basic *mlb, char c, int i, int j)
{
	long double EPSILON;
	double x1 = mlb->map[i][j].x;
	double y1 = mlb->map[i][j].y;
	double x2 = mlb->map[i + 1][j].x;
	double y2 = mlb->map[i + 1][j].y;

	EPSILON = 0.1;
	if (c == 'i')
		if (((mlb->xy[0] <= fmin(x1, x2) - EPSILON || mlb->xy[0] >= fmax(x1, x2) + EPSILON) ||
			 (mlb->xy[1] <= fmin(y1, y2) - EPSILON || mlb->xy[1] >= fmax(y1, y2) + EPSILON)))
			return 1;
	x2 = mlb->map[i][j + 1].x;
	y2 = mlb->map[i][j + 1].y;
	if (c == 'j')
		if (((mlb->xy[0] <= fmin(x1, x2) - EPSILON || mlb->xy[0] >= fmax(x1, x2) + EPSILON) ||
			 (mlb->xy[1] <= fmin(y1, y2) - EPSILON || mlb->xy[1] >= fmax(y1, y2) + EPSILON)))
			return 1;
	return 0;
}

int check_line(basic *mlb)
{
	int i;
	int j;

	i = -1;
	j = -1;
	while (++i < mlb->nr_line - 1)
	{
		while (++j < mlb->nr_p_line)
		{
			if (i != mlb->nr_line - 2)
				if (check_is_between(mlb, 'i', i, j) == 0)
					if (gradients(mlb, 'i', i, j) == 0)
						return (0);
			if (j != mlb->nr_p_line - 1)
				if (check_is_between(mlb, 'j', i, j) == 0)
					if (gradients(mlb, 'j', i, j) == 0)
						return (0);
		}
		j = -1;
	}
	return 1;
}

void set_pixel(char *img_data, basic *mlb, int color)
{
	int pixel_index;

	pixel_index = (mlb->y0 * mlb->size_line) + (mlb->x0 * (mlb->bpp / 8));
	*(unsigned int *)(img_data + pixel_index) = color;
}
