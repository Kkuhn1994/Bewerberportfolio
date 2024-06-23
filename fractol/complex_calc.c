/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   complex_calc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkuhn <kkuhn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 14:51:57 by kkuhn             #+#    #+#             */
/*   Updated: 2024/05/28 18:36:47 by kkuhn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

t_complex	multiply(t_complex a, t_complex b)
{
	t_complex	result;

	result.real = a.real * b.real - a.imag * b.imag;
	result.imag = a.real * b.imag + b.real * a.imag;
	return (result);
}

t_complex	addition(t_complex a, t_complex b)
{
	t_complex	result;

	result.real = a.real + b.real;
	result.imag = a.imag + b.imag;
	return (result);
}

t_complex	substraction(t_complex a, t_complex b)
{
	t_complex	result;

	result.real = a.real - b.real;
	result.imag = a.imag - b.imag;
	return (result);
}

t_complex	division(t_complex a, t_complex b)
{
	t_complex	konjugat;
	t_complex	result;
	double		divisor;

	konjugat.real = b.real;
	konjugat.imag = b.imag;
	result.real = 0;
	result.imag = 0;
	divisor = b.real * b.real + b.imag * b.imag;
	if (divisor == 0)
	{
		result.real = INFINITY;
		result.imag = INFINITY;
	}
	else
	{
		result.real = (a.real * b.real + a.imag * b.imag) / divisor;
		result.imag = (a.imag * b.real - a.real * b.imag) / divisor;
	}
	return (result);
}

double	betrag(t_complex a)
{
	double	betrag;

	betrag = sqrt(pow(a.real, 2) + pow(a.imag, 2));
	return (betrag);
}
