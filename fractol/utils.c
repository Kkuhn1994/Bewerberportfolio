/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkuhn <kkuhn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 15:26:05 by kkuhn             #+#    #+#             */
/*   Updated: 2024/05/27 15:26:29 by kkuhn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	set_coordinate(double x, double y, double **xy)
{
	xy[0][0] = x;
	xy[0][1] = y;
}

t_complex	setcomplex(double real, double imag)
{
	t_complex	c;

	c.real = real;
	c.imag = imag;
	return (c);
}

void	set_pixel(char *img_data, int *xy, int color)
{
	int	pixel_index;

	pixel_index = (xy[1] * xy[3]) + (xy[0] * (xy[2] / 8));
	*(unsigned int *)(img_data + pixel_index) = color;
}

void	setrgb(float **rgb, float c, float x, float o)
{
	rgb[0][0] = c;
	rgb[0][1] = x;
	rgb[0][2] = o;
}

double	*calc_xy(double *px, double *Opunkt, t_data *data)
{
	double	x;
	double	y;

	x = px[0];
	y = px[1];
	x = (x - Opunkt[0]) / 200 / (data->zoom);
	y = (y - Opunkt[1]) / 200 / (data->zoom);
	px[0] = x;
	px[1] = y;
	return (px);
}
