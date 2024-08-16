/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkuhn <kkuhn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 18:09:57 by kkuhn             #+#    #+#             */
/*   Updated: 2024/08/14 18:10:18 by kkuhn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	sleeptime(t_philo *philo)
{
	philo->start_sleep = gettime();
	write_message("sleeps", philo, COLOR_CYAN);
	while (gettime() - philo->start_sleep < philo->time_to_sleep)
		usleep(100);
}

void	think(t_philo *philo)
{
	philo->start_think = gettime();
	philo->time_to_think = (philo->time_to_die
			- (gettime() - philo->start_eat)) * 0.5;
	write_message("thinks", philo, COLOR_YELLOW);
	while (gettime() - philo->start_think < philo->time_to_think)
		usleep(100);
}

void	take_forks(t_philo *philo)
{
	sem_wait(philo->data->arbitrator);
	sem_wait(philo->data->forks);
	write_message("takes r fork", philo, COLOR_GREEN);
	sem_wait(philo->data->forks);
	write_message("takes l fork", philo, COLOR_GREEN);
	sem_post(philo->data->arbitrator);
}

void	eating(t_philo *philo)
{
	philo->start_eat = gettime();
	write_message("eats", philo, COLOR_MAGENTA);
	while (gettime() < philo->start_eat + philo->time_to_eat)
		usleep(100);
}

void	drop_forks(t_philo *philo)
{
	sem_post(philo->data->forks);
	write_message("dropped fork", philo, COLOR_BLUE);
	sem_post(philo->data->forks);
	write_message("dropped fork", philo, COLOR_BLUE);
}
