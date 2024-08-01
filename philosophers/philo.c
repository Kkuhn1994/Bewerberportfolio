/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkuhn <kkuhn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 15:30:03 by kkuhn             #+#    #+#             */
/*   Updated: 2024/08/01 20:52:52 by kkuhn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <sys/time.h>

#include <stdlib.h>
#include <stdio.h> 
#include <pthread.h>
#include "libft/libft.h"

int	init(t_data *data, int argc, char *argv[])
{
	int	i;
	int	j;

	i = 0;
	j = -1;
	// while (i < argc)
	// {
	// 	while (argv[i][++ j] != 0)
	// 		if (isdigit((int)argv[i][j]) != 0)
	// 			return (1);
	// 	j = -1;
	// 	i ++;
	// }
	if (argc < 5 || argc > 6)
		return (1);
	data->num_philo = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	data->write = malloc (sizeof(pthread_mutex_t));
	if (argc == 6)
		data->num_meals = ft_atoi(argv[5]);
	else
		data->num_meals = -1;
	return (0);
}

int	check(t_data data)
{
	if (data.num_philo < 0 || data.num_philo > 200)
	{
		ft_putstr_fd("number philo invalid", 1);
		return (1);
	}
	if (data.time_to_die < 0 || data.time_to_eat < 0 || data.time_to_sleep < 0)
	{
		ft_putstr_fd("time invalid", 1);
		return (1);
	}
	return (0);
}

time_t	gettime(void)
{
	struct		timeval tv;
	time_t		time;

	gettimeofday(&tv, NULL);
	time = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	return (time);
}

void	init_threads(t_data *data)
{
	int	i;

	i = 0;
	data->forks = malloc (data->num_philo * sizeof(pthread_mutex_t));
	data->threads = malloc (data->num_philo * sizeof(pthread_t));
	data->philos = malloc (data->num_philo * sizeof(t_philo *));
	data->philos[0].l = &data->forks[data->num_philo - 1];
	data->philos[0].r = &data->forks[0];
	while (i < data->num_philo)
	{
		if (i != 0)
			data->philos[i].l = &data->forks[i - 1];
		if (i != 0)
			data->philos[i].r = &data->forks[i];
		data->philos[i].start_time = data->start_time;
		data->philos[i].time_to_die = data->time_to_die;
		data->philos[i].time_to_eat = data->time_to_eat;
		data->philos[i].time_to_sleep = data->time_to_sleep;
		data->philos[i].num_meals = data->num_meals;
		data->philos[i].id = i + 1;
		data->philos[i].data = data;
		i ++;
	}
}


void write_message(char *action, t_philo *philo)
{
	char *time;

	pthread_mutex_lock(philo->data->write);
	ft_putstr_fd("philo", 1);
	ft_putstr_fd(" ", 1);
	ft_putstr_fd(ft_itoa(philo->id), 1);
	ft_putstr_fd(" ", 1);
	ft_putnbr_fd((int)(gettime() - philo->start_time), 1);
	ft_putstr_fd(" ", 1);
	ft_putstr_fd(action, 1);
	ft_putstr_fd("\n", 1);
	pthread_mutex_unlock(philo->data->write);
}

void	unlock_left_and_right(t_philo *philo)
{
	size_t id;
	t_data *data;

	id = philo->id;
	data = philo->data;
	pthread_mutex_unlock(&data->philos[id - 1].arbitrator);
	pthread_mutex_unlock(&data->philos[id + 1].arbitrator);
}

void	lock_left_and_right(t_philo *philo)
{
	size_t id;
	t_data *data;

	id = philo->id;
	data = philo->data;
	pthread_mutex_lock(&data->philos[id - 1].arbitrator);
	pthread_mutex_lock(&data->philos[id + 1].arbitrator);
}

int check_for_forks(void *input)
{
	t_philo *philo;

	philo = input;
	
	lock_left_and_right(philo);
	pthread_mutex_lock(&philo->arbitrator);
	pthread_mutex_lock(philo->l);
	pthread_mutex_lock(philo->r);
	pthread_mutex_unlock(philo->l);
	pthread_mutex_unlock(philo->r);
	pthread_mutex_unlock(&philo->arbitrator);
	
	return 0;
}

void *routine(void *input)
{
	t_philo *philo;
	time_t	start_eat;

	philo = input;
	while (gettime() < philo->start_time)
		usleep(100) ;
	if (philo->id % 2 == 0)
		while (gettime() < philo->start_time + philo->time_to_eat)
			usleep(100) ;
	pthread_mutex_lock(philo->l);
	write_message("takes left fork", philo);
	pthread_mutex_lock(philo->r);
	write_message("takes right fork", philo);
	start_eat = gettime();
	write_message("eats", philo);
	while (gettime() < start_eat + philo->time_to_eat)
		usleep(100) ;
	pthread_mutex_unlock(philo->l);
	write_message("dropped left fork", philo);
	pthread_mutex_unlock(philo->r);
	write_message("dropped right fork", philo);
	return 0;
}


void threads(t_data *data)
{
	int	i;

	init_threads(data);
	i = -1;
	pthread_mutex_init(data->write, NULL);
	while (++ i < data->num_philo)
		pthread_mutex_init(&data->forks[i], NULL);
	i = -1;
	while (++ i < data->num_philo)
		pthread_create(&data->threads[i], 0, &routine, &data->philos[i]);
	i = -1;
	printf("test");
	while  (++ i < data->num_philo)
		pthread_join(data->threads[i], 0);
	i = -1;
	printf("test");
	while (++ i < data->num_philo)
		pthread_mutex_destroy(&data->forks[i]);
		printf("test");
	pthread_mutex_destroy(data->write);
	
}



int	main(int argc, char *argv[])
{
	t_data	data;

	data.start_time = gettime() + 10;
	// argv[1] = "3";
	// argv[2] = "100";
	// argv[3] = "100";
	// argv[4] = "100";
	// argv[5] = "100";
	// argc = 6;
	if (init(&data, argc, argv) != 0)
		exit_programm("not enough, too many or wrong arguments");
	if (check(data) != 0)
		return (0);
	
	threads(&data);
	return 0;
}
