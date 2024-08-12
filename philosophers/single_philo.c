/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_philo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkuhn <kkuhn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 15:28:46 by kkuhn             #+#    #+#             */
/*   Updated: 2024/08/12 14:01:58 by kkuhn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*single_philo(void *input)
{
	t_data	*data;

	data = input;
	while (gettime() < data->start_time)
		usleep(100);
	pthread_mutex_lock(&data->forks[0]);
	write_message("has taken a fork", &data->philos[0], COLOR_CYAN);
	while (gettime() < data->start_time + data->time_to_die)
		usleep(100);
	write_message("died", &data->philos[0], COLOR_RED);
	pthread_mutex_unlock(&data->forks[0]);
	return (NULL);
}
