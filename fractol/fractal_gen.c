/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractal_gen.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkuhn <kkuhn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 23:00:33 by kkuhn             #+#    #+#             */
/*   Updated: 2024/05/28 20:46:50 by kkuhn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	hsl_to_rgb(float *hsl, int *r, int *g, int *b)
{
	float	c;
	float	x;
	float	m;
	float	*rgb;

	c = (1 - fabs(2 * hsl[2] - 1)) * hsl[1];
	x = c * (1 - fabs(fmod(hsl[0] / 60.0, 2) - 1));
	m = hsl[2] - c / 2;
	rgb = malloc (3 * sizeof(float));
	if (0 <= hsl[0] && hsl[0] < 60)
		setrgb(&rgb, c, x, 0);
	else if (60 <= hsl[0] && hsl[0] < 120)
		setrgb(&rgb, x, c, 0);
	else if (120 <= hsl[0] && hsl[0] < 180)
		setrgb(&rgb, 0, c, x);
	else if (180 <= hsl[0] && hsl[0] < 240)
		setrgb(&rgb, 0, x, c);
	else if (240 <= hsl[0] && hsl[0] < 300)
		setrgb(&rgb, x, 0, c);
	else
		setrgb(&rgb, c, 0, x);
	*r = (int)((rgb[0] + m) * 255);
	*g = (int)((rgb[1] + m) * 255);
	*b = (int)((rgb[2] + m) * 255);
	free(rgb);
}

int	calculate_color(int iterations, t_data *data)
{
	float	*hsl;
	int		red;
	int		green;
	int		blue;

	if (iterations == -1)
		return (0x000000);
	hsl = malloc (3 * sizeof (float));
	hsl[0] = 360.0 * (data->i - iterations) / data->i;
	hsl[1] = 0.5;
	hsl[2] = 0.5;
	hsl_to_rgb(hsl, &red, &green, &blue);
	red = red * data->red;
	blue = data->blue * blue;
	green = data->green * green;
	free(hsl);
	return ((red << 16) | (green << 8) | blue);
}

int	nextpixel(int *x, int *y, int xmax, int ymax)
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

int	decide_color(t_data *data, double *pixel, double *null_punkt, int *xy)
{
	t_complex	c ;
	t_complex	z ;
	int			color;

	set_coordinate(data->x0, data->y0, &pixel);
	pixel = calc_xy(pixel, null_punkt, data);
	c = setcomplex(data->creal, data->cimag);
	z = setcomplex(pixel[0], pixel[1]);
	if (ft_memcmp(data->name_set, "Julia", 5) == 0)
		color = calculate_color(is_julia(z, c, data), data);
	else if (ft_memcmp(data->name_set, "Mandelbrot", 10) == 0)
		color = calculate_color(is_mandelbrot(z, data), data);
	else if (ft_memcmp(data->name_set, "Newton", 6) == 0)
		color = check_newton(z);
	else
	{
		write(1, "Invalid Set\n", 12);
		free(pixel);
		free(xy);
		exit(0);
	}
	return (color);
}

int	visualize(t_data *data, double *null_punkt)
{
	double	*pixel;
	int		color;
	void	*ptr ;
	char	*idata;
	int		*xy;

	xy = malloc (4 * sizeof (int));
	pixel = malloc (2 * sizeof(double));
	data->x0 = 0;
	data->y0 = 0;
	ptr = mlx_new_image(data->mlx_ptr, 2000, 2000);
	idata = mlx_get_data_addr(ptr, &data->bpp, &data->size, &data->end);
	while (1)
	{
		ft_shortenfunction(data, xy);
		color = decide_color(data, pixel, null_punkt, xy);
		set_pixel(idata, xy, color);
		if (nextpixel(&data->x0, &data->y0, data->x1, data->y1) == 0)
			break ;
	}
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, ptr, 0, 0);
	mlx_destroy_image(data->mlx_ptr, ptr);
	return (free(pixel), free(xy), 0);
}
