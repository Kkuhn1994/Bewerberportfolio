/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkuhn <kkuhn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 22:51:55 by kkuhn             #+#    #+#             */
/*   Updated: 2024/03/19 22:51:57 by kkuhn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include <stddef.h>
#include <unistd.h>
#include "ft_printf.h"

void	ft_putnbrhexptr(unsigned long hex, int *counter)
{
	char	*base;

	base = "0123456789abcdef";
	if ((hex / 16) == 0)
	{
		*counter += write(1, &base[hex % 16], 1);
		return ;
	}
	ft_putnbrhexptr(hex / 16, counter);
	*counter += write(1, &base[hex % 16], 1);
}

void	ft_putnbrhexa(unsigned int hex, int *counter, char prefix)
{
	char	*base;

	if (prefix == 'x')
		base = "0123456789abcdef";
	else
		base = "0123456789ABCDEF";
	if ((hex / 16) == 0)
	{
		*counter += write(1, &base[hex % 16], 1);
		return ;
	}
	ft_putnbrhexa(hex / 16, counter, prefix);
	*counter += write(1, &base[hex % 16], 1);
}

void	ft_flag(const char prefix, va_list arguments, int *counter)
{
	if (prefix == 'd' || prefix == 'i')
		ft_putnbr(va_arg(arguments, int), counter);
	if (prefix == 's')
		ft_putstr(va_arg(arguments, char *), counter);
	if (prefix == 'c')
		ft_putchar(va_arg(arguments, int), counter);
	if (prefix == 'X' || prefix == 'x')
		ft_putnbrhexa(va_arg(arguments, int), counter, prefix);
	if (prefix == 'p')
	{
		ft_putstr("0x", counter);
		ft_putnbrhexptr(va_arg(arguments, unsigned long), counter);
	}
	if (prefix == 'u')
		ft_putunbr(va_arg(arguments, unsigned int), counter);
}

int	ft_printf(const char *prefix, ...)
{
	va_list	arguments;
	int		counter_character_print;

	counter_character_print = 0;
	va_start(arguments, prefix);
	if (!prefix)
		return (0);
	while (*prefix != 0)
	{
		if (*prefix == '%')
		{
			if (prefix[1] == '%')
				counter_character_print += write(1, "%", 1);
			else
				ft_flag(prefix[1], arguments, &counter_character_print);
			prefix ++;
		}
		else
			counter_character_print += write(1, prefix, 1);
		prefix ++;
	}
	return (counter_character_print);
}

// int main(void)
// {
// 	printf("%d\n",ft_printf(" %p ", 1));
// 	printf("%d",printf(" %X ", -1));
// }