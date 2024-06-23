/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_mandelbrot.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkuhn <kkuhn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 14:27:44 by kkuhn             #+#    #+#             */
/*   Updated: 2024/05/28 20:40:23 by kkuhn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	close_win(t_data *data)
{
	mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	exit(0);
}

void	ft_shortenfunction(t_data *data, int *xy)
{
	xy[0] = data->x0;
	xy[1] = data->y0;
	xy[2] = data->bpp;
	xy[3] = data->size;
}

int	check_periodic(t_complex z, t_complex *z_store, int i)
{
	int	j;

	j = 0;
	while (j < i)
	{
		if (z.real == z_store[i].real && z.imag == z_store[i].imag)
			return (1);
		j ++;
	}
	return (0);
}

int	is_mandelbrot(t_complex c, t_data *data)
{
	int			i;
	t_complex	z;
	t_complex	*store_z;

	store_z = malloc (data->i * sizeof(t_complex));
	z.real = 0;
	z.imag = 0;
	i = 0;
	while (i < data->i)
	{
		z = addition(multiply(z, z), c);
		if (check_periodic(z, store_z, i) != 0)
			break ;
		if (betrag(z) > 2.0)
		{
			free(store_z);
			return (i);
		}
		store_z[i] = z;
		i ++;
	}
	free(store_z);
	return (-1);
}
