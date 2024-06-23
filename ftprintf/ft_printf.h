/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkuhn <kkuhn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 22:48:31 by kkuhn             #+#    #+#             */
/*   Updated: 2024/04/09 18:27:24 by kkuhn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <stddef.h>
# include <unistd.h>

int		ft_printf(char const *prefix, ...);
void	ft_putnbr(int n, int *counter_character_print);
void	ft_flag(const char prefix, va_list arguments, int *counter);
void	ft_putnbrhexptr(unsigned long hex, int *counter);
void	ft_putnbrhexa(unsigned int hex, int *counter, char prefix);
void	ft_putchar(char c, int *counter);
void	ft_putstr(char *s, int *counter_str_len);
void	ft_putunbr(unsigned int n, int *counter_character_print);
void	ft_putnbr(int n, int *counter_character_print);

#endif