/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_julia.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkuhn <kkuhn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 14:27:37 by kkuhn             #+#    #+#             */
/*   Updated: 2024/05/28 20:47:22 by kkuhn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	shift_colors(t_data *data, int keysym)
{
	if (keysym == 15)
		data->red += 1;
	if (keysym == 16)
		data->blue += 1;
	if (keysym == 17)
		data->green += 1;
}

int	is_julia(t_complex z, t_complex c, t_data *data)
{
	int	result;

	result = 0;
	while (result < data->i)
	{
		z = addition(multiply(z, z), c);
		if (betrag(z) > 2.0)
			return (result);
		result ++;
	}
	return (-1);
}
