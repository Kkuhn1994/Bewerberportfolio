#ifndef FDF_H
#define FDF_H

#include "MLX42/include/MLX42/MLX42.h"
#include "libft/libft.h"
#include <fcntl.h>
#include <sys/fcntl.h>
#include <math.h>

typedef struct xyz
{
	long double x;
	long double y;
	long double z;
} matrix;

typedef struct basic
{
	matrix **map;
	mlx_t *mlx_ptr;
	mlx_image_t *img;
	int x0;
	int y0;
	int endian;
	int bpp;
	int size_line;
	long double factor;
	int null_punkt[2];
	int nr_line;
	int nr_p_line;
	long double xy[2];
	bool rotate_x;
	bool rotate_z;
	bool rotate_y;
} basic;

int *count_ints(int *old_array, int nr_newline);
int is_rectangular(int *int_per_line, int size);
void free_map(long double **map);
void free_map2(matrix **map);
char *ft_strjoin2(char *s1, char *s2);
long double *ft_join_double_ptr(long double *ptr1, long double ptr2, int arraysize);
long double *gnl(int fd, int i, int *int_per_line);
long double **loadmap(char *file, int **int_per_line, int *nr_line);
long double **add_line(long double **map, long double *line);
int check_point(basic *mlb);
int gradients(basic *mlb, char c, int i, int j);
int check_line(basic *mlb);
void set_pixel(char *img_data, basic *mlb, int color);
void rotate_z(basic *mlb);
void rotate_y(basic *mlb);
void rotate_x(basic *mlb);
matrix **convert_to_matrix(long double **map, int x, int y);
void key_callback(mlx_key_data_t keydata, void *ml);
void scroll_callback(double xdelta, double ydelta, void *param);
int nextpixel(int *x, int *y, int xmax, int ymax);

#endif