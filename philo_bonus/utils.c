/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkuhn <kkuhn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 18:07:20 by kkuhn             #+#    #+#             */
/*   Updated: 2024/08/15 20:34:34 by kkuhn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	write_message(char *action, t_philo *philo, char *color)
{
	char	*id_string;

	sem_wait(philo->data->write);
	ft_putstr_fd(color, 1);
	ft_putstr_fd("philo", 1);
	ft_putstr_fd(" ", 1);
	id_string = ft_itoa(philo->id);
	ft_putstr_fd(id_string, 1);
	free(id_string);
	ft_putstr_fd(" ", 1);
	ft_putnbr_fd((int)(gettime() - philo->start_time), 1);
	ft_putstr_fd(" ", 1);
	ft_putstr_fd(action, 1);
	ft_putstr_fd("\n", 1);
	ft_putstr_fd(COLOR_RESET, 1);
	sem_post(philo->data->write);
}

time_t	gettime(void)
{
	struct timeval	tv;
	time_t			time;

	gettimeofday(&tv, NULL);
	time = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	return (time);
}

void	exit_programm(char *errormessage)
{
	ft_putstr_fd(errormessage, 2);
	exit(1);
}

int	check(t_data *data)
{
	if (data->num_philo > 200)
	{
		ft_putstr_fd("number philo invalid", 1);
		return (1);
	}
	if (data->time_to_die < 0 || data->time_to_eat < 0
		|| data->time_to_sleep < 0)
	{
		ft_putstr_fd("time invalid", 1);
		return (1);
	}
	return (0);
}

int	ft_isdigit(int a)
{
	if (a >= 48 && a <= 57)
		return (1);
	else
		return (0);
}
