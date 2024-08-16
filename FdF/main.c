#include "fdf.h"

void visualize(void *ml)
{
	basic *mlb;
	char *imgdata;

	mlb = (basic *)ml;
	mlx_delete_image(mlb->mlx_ptr, mlb->img);
	mlb->img = mlx_new_image(mlb->mlx_ptr, 800, 800);
	mlb->x0 = 0;
	mlb->y0 = 0;
	while (1)
	{
		mlb->xy[0] = (mlb->x0 - mlb->null_punkt[0]) / mlb->factor;
		mlb->xy[1] = (mlb->null_punkt[1] - mlb->y0) / mlb->factor;
		if (mlb->x0 > 50 && mlb->x0 < 750 && mlb->y0 > 50 && mlb->y0 < 750)
		{
			if (check_point(mlb) == 0)
				mlx_put_pixel(mlb->img, mlb->x0, mlb->y0, 0xFFFFFF);
			else if (check_line(mlb) == 0)
				mlx_put_pixel(mlb->img, mlb->x0, mlb->y0, 0xFFAAFF);
		}
		if (nextpixel(&mlb->x0, &mlb->y0, 1000, 1000) == 0)
			break;
	}
	mlx_image_to_window(mlb->mlx_ptr, mlb->img, 0, 0);
	return;
}

void mlx_part(matrix **map, int nr_per_line, int nr_line)
{
	basic minilib;
	void *key;

	minilib.map = map;
	minilib.null_punkt[0] = 400;
	minilib.null_punkt[1] = 400;
	minilib.nr_line = nr_line;
	minilib.nr_p_line = nr_per_line;
	minilib.mlx_ptr = mlx_init(800, 800, "FDf", false);
	if (nr_line > nr_per_line)
		minilib.factor = 600 / nr_line;
	else
		minilib.factor = 600 / nr_per_line;
	mlx_loop_hook(minilib.mlx_ptr, &visualize, (void *)&minilib);
	mlx_key_hook(minilib.mlx_ptr, key_callback, (void *)&minilib);
	mlx_scroll_hook(minilib.mlx_ptr, scroll_callback, NULL);
	mlx_loop(minilib.mlx_ptr);
}

int main(int argc, char *argv[])
{
	long double **map;
	matrix **xyzmap;
	int *int_per_line;
	int nr_lines;

	int i = 0;
	int j = 0;

	int_per_line = malloc(1 * sizeof(int));
	int_per_line[0] = 0;
	map = loadmap("input.fdf", &int_per_line, &nr_lines);
	if (map == 0)
		return 0;
	xyzmap = convert_to_matrix(map, *int_per_line, nr_lines);

	mlx_part(xyzmap, *int_per_line, nr_lines);
	free_map(map);
	free_map2(xyzmap);
	free(int_per_line);
	return 0;
}