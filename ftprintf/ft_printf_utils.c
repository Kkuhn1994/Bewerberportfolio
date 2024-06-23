/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkuhn <kkuhn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 22:46:49 by kkuhn             #+#    #+#             */
/*   Updated: 2024/03/19 22:46:59 by kkuhn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include <stddef.h>
#include <unistd.h>
#include "ft_printf.h"

void	ft_putchar(char c, int *counter)
{
	write(1, &c, 1);
	*counter = *counter + 1;
}

void	ft_putstr(char *s, int *counter_str_len)
{
	if (!s)
	{
		*counter_str_len += write(1, "(null)", 6);
		return ;
	}
	while (*s != 0)
	{
		write(1, s, 1);
		*counter_str_len = *counter_str_len + 1;
		s ++;
	}
}

void	ft_putunbr(unsigned int n, int *counter_character_print)
{
	char	res;

	if (n > 9)
		ft_putnbr(n / 10, counter_character_print);
	res = (n % 10) + '0';
	*counter_character_print += write(1, &res, 1);
}

void	ft_putnbr(int n, int *counter_character_print)
{
	char	res;

	if (n == -2147483648)
	{
		ft_putnbr(n / 10, counter_character_print);
		*counter_character_print += write(1, "8", 1);
	}
	else if (n < 0)
	{
		*counter_character_print += write(1, "-", 1);
		ft_putnbr(-n, counter_character_print);
	}
	else
	{
		if (n > 9)
			ft_putnbr(n / 10, counter_character_print);
		res = (n % 10) + '0';
		*counter_character_print += write(1, &res, 1);
	}
}
