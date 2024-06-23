/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkuhn <kkuhn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 14:24:53 by kkuhn             #+#    #+#             */
/*   Updated: 2024/05/28 20:52:23 by kkuhn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H
# include "libft/libft.h"
# include <stdio.h>
# include <fcntl.h>
# include <stdlib.h>
# include <math.h>
# include "minilibx/mlx.h"

# define ESC_KEY 53

typedef struct fractol{
	double	real;
	double	imag;
}	t_complex;

typedef struct s_data
{
	void	*mlx_ptr;
	void	*win_ptr;
	int		iterations;
	char	*name_set;
	double	zoom_old;
	double	zoom;
	double	nullx;
	double	nully;
	int		mouse_x;
	int		mouse_y;
	double	creal;
	double	cimag;
	int		iterations2;
	int		iterations3;
	int		iterations4;
	int		iterations5;
	int		iterations6;
	int		iterations7;
	int		iterations8;
	int		iterations9;
	int		iterations10;
	int		x0;
	int		y0;
	int		x1;
	int		y1;
	int		bpp;
	int		end;
	int		size;
	int		i;
	int		red;
	int		blue;
	int		green;

}	t_data;

void		shift_colors(t_data *data, int keysym);
t_complex	multiply(t_complex a, t_complex b);
t_complex	addition(t_complex a, t_complex b);
double		*calc_xy(double *px, double *Opunkt, t_data *data);
int			visualize(t_data *data, double *null_punkt);
double		betrag(t_complex a);
int			is_julia(t_complex z, t_complex c, t_data *data);
int			is_mandelbrot(t_complex c, t_data *data);
t_complex	division(t_complex a, t_complex b);
int			check_newton(t_complex number);
t_complex	substraction(t_complex a, t_complex b);
void		set_coordinate(double x, double y, double **xy);
t_complex	setcomplex(double real, double imag);
void		set_pixel(char *img_data, int *xy, int color);
void		setrgb(float **rgb, float c, float x, float o);
void		set_coordinate(double x, double y, double **xy);
t_data		*calc_nullpunkt(t_data *data);
double		ft_atodouble(char *string);
void		set_data(t_data *data, char *argv[], int argc);
int			print_fractal_options(char *argv[], int argc);
double		ft_atodouble(char *string);
void		ft_shortenfunction(t_data *data, int *xy);
void		close_win(t_data *data);

#endif