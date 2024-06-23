/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   newton.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkuhn <kkuhn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 14:45:21 by kkuhn             #+#    #+#             */
/*   Updated: 2024/05/28 20:05:29 by kkuhn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

t_complex	function(t_complex number)
{
	t_complex	one;

	one.real = 1;
	one.imag = 0;
	number = substraction(multiply(multiply(number, number), number), one);
	return (number);
}

t_complex	fdx(t_complex number)
{
	t_complex	factor;
	t_complex	one;

	one.real = 1;
	one.imag = 0;
	factor.real = 3;
	factor.imag = 0;
	number = multiply(multiply(number, number), factor);
	return (number);
}

t_complex	newton_rhapson(t_complex number)
{
	number = substraction(number, division(function(number), fdx(number)));
	return (number);
}

int	check_newton(t_complex number)
{
	int			i;
	t_complex	null1;
	t_complex	null2;
	t_complex	null3;

	i = 0;
	null1.real = 1;
	null1.imag = 0;
	null2.real = -0.5;
	null2.imag = sqrt(3) / 2;
	null3.real = -0.5;
	null3.imag = - (sqrt(3) / 2);
	while (i < 100)
	{
		number = newton_rhapson(number);
		if (betrag(substraction(number, null1)) < 0.1)
			return ((i * 10 % 256) << 16);
		if (betrag(substraction(number, null2)) < 0.1)
			return ((i * 10 % 256) << 8);
		if (betrag(substraction(number, null3)) < 0.1)
			return (i * 10 % 256);
		i ++;
	}
	return (0xFFFFFF);
}
