#include "fdf.h"

void key_callback(mlx_key_data_t keydata, void *ml)
{
	basic *mlb;
	mlb = ml;

	printf("Key pressed: %d\n", keydata.key);
	if (keydata.key == 87)
		mlb->null_punkt[1] = mlb->null_punkt[1] - 50;
	if (keydata.key == 83)
		mlb->null_punkt[1] = mlb->null_punkt[1] + 50;
	if (keydata.key == 65)
		mlb->null_punkt[0] = mlb->null_punkt[0] - 50;
	if (keydata.key == 68)
		mlb->null_punkt[0] = mlb->null_punkt[0] + 50;
	if (keydata.key == 88)
		rotate_x(mlb);
	if (keydata.key == 90)
		rotate_y(mlb);
	if (keydata.key == 67)
		rotate_z(mlb);
}

void scroll_callback(double xdelta, double ydelta, void *param)
{
	printf("%f\n", xdelta);
}

int nextpixel(int *x, int *y, int xmax, int ymax)
{
	if (*x == xmax && *y == ymax)
		return (0);
	if (*x != xmax)
		*x = *x + 1;
	else if (*x == xmax)
	{
		*x = 0;
		*y = *y + 1;
	}
	else
		*y = *y + 1;
	return (1);
}