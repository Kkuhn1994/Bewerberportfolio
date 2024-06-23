/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkuhn <kkuhn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 15:25:48 by kkuhn             #+#    #+#             */
/*   Updated: 2024/05/28 20:45:20 by kkuhn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

t_data	*calc_nullpunkt(t_data *data)
{
	data->nullx = data->mouse_x + (data->nullx - data->mouse_x)
		* (data->zoom / data->zoom_old);
	data->nully = data->mouse_y + (data->nully - data->mouse_y)
		* (data->zoom / data->zoom_old);
	return (data);
}

int	ft_atoi2(const char *number)
{
	int	num;
	int	is_negative;

	is_negative = 1;
	num = 0;
	while (*number != 0 && *number != '.')
	{
		if (*number == '-')
			is_negative = -is_negative;
		else if (*number >= '0' && *number <= '9')
			num = num * 10 + *number - '0';
		else if (!(*number >= '0' && *number <= '9'))
		{
			write(1, "Invalid Parameter\n", 19);
			exit(0);
		}
		number ++;
	}
	return (num * is_negative);
}

double	ft_atodouble(char *string)
{
	double	number_int;
	double	number_decimal;
	int		divider;
	double	result;

	divider = 1;
	result = 1;
	number_int = ft_atoi2(string);
	if (*string == '-')
		result = -1;
	while (*string != '.' && *string != 0)
		string ++;
	if (*string == '.')
		string ++;
	number_decimal = ft_atoi2(string);
	while (*string != 0)
	{
		divider = divider * 10;
		string ++;
	}
	if (number_int >= 0 && result == 1)
		result = number_int + number_decimal / divider;
	else
		result = number_int - number_decimal / divider;
	return (result);
}

void	set_data(t_data *data, char *argv[], int argc)
{
	data->nullx = 500;
	data->nully = 500;
	data->nullx = 500;
	data->nully = 500;
	data->zoom = 1;
	data->zoom_old = 1;
	data->creal = 0;
	data->cimag = 0;
	if (argc == 4)
	{
		data->creal = ft_atodouble(argv[2]);
		data->cimag = ft_atodouble(argv[3]);
	}
	data->x0 = 0;
	data->y0 = 0;
	data->x1 = 1000;
	data->y1 = 1000;
	data->i = 300;
	data->red = 1;
	data->green = 1;
	data->blue = 1;
}

int	print_fractal_options(char *argv[], int argc)
{
	if (argc < 2)
	{
		write(1, "Mandelbrot\n", 11);
		write(1, "Julia\n", 6);
		write(1, "Newton\n", 7);
		return (0);
	}
	if (ft_memcmp(argv[1], "Julia", 5) == 0 && argc != 4)
	{
		write(1, "good option for C:\n", 20);
		write(1, "-0.4 0.8\n", 9);
		return (0);
	}
	return (1);
}
