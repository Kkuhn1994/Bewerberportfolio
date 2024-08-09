/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkuhn <kkuhn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 15:30:03 by kkuhn             #+#    #+#             */
/*   Updated: 2024/08/09 16:06:49 by kkuhn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// void file_write(char *message, t_philo *philo){
// 	pthread_mutex_lock(&philo->data->arbitrator2);
// 	int fd = open("output.txt", O_WRONLY | O_APPEND | O_CREAT);
// 	write(fd, message, ft_strlen(message));
// 	close(fd);
// 	pthread_mutex_unlock(&philo->data->arbitrator2);
// }

void	*routine(void *input)
{
	t_philo	*philo;

	philo = input;
	while (gettime() < philo->start_time)
		usleep(100);
	if (philo->id % 2 == 0)
		while (gettime() < philo->start_time + 3 * philo->time_to_eat)
			usleep(100);
	while (philo->philo_died != 1 && philo->num_meals > philo->nrmeals)
	{
		take_forks(philo);
		eating(philo);
		drop_forks(philo);
		philo->nrmeals++;
	}
	return (NULL);
}

void	*grimreaper(void *input)
{
	int		i;
	t_data	*data;

	data = input;
	while (data->finished == 0)
	{
		i = -1;
		while (++ i < data->num_philo)
		{
			if (data->philos[i].philo_died == 1)
			{
				i++;
				continue ;
			}
			pthread_mutex_lock(&data->philos[i].arbitrator);
			if (gettime() - data->philos[i].last_time_eat >= data->time_to_die
				&& gettime() - data->philos[i].start_eat >= data->time_to_die)
			{
				data->philos[i].philo_died = 1;
				write_message("died", &data->philos[i]);
			}
			pthread_mutex_unlock(&data->philos[i].arbitrator);
		}
	}
	return (NULL);
}

void mutex_init(t_data *data)
{
	int i;
	
	pthread_mutex_init(&data->write, NULL);
	pthread_mutex_init(&data->arbitrator2, NULL);
	i = 0;
	while(i < data->num_philo)
	{
		pthread_mutex_init(&data->philos[i].arbitrator, NULL);
		pthread_mutex_init(&data->forks[i], NULL);
		i ++;
	}
}


void threads(t_data *data)
{
	int	i;

	init_threads(data);

	i = -1;
	mutex_init(data);
	// pthread_create(&data->threads[data->num_philo], 0, &grimreaper, data);
	while (++ i < data->num_philo)
		pthread_create(&data->threads[i], 0, &routine, &data->philos[i]);
	i = -1;
	while (++ i < data->num_philo)
		pthread_join(data->threads[i], 0);
	data->finished = 1;
	// pthread_join(data->threads[i], 0);
	i = -1;
	while (++ i < data->num_philo)
	{
		pthread_mutex_destroy(&data->philos[i].arbitrator);
		pthread_mutex_destroy(&data->forks[i]);
	}
	pthread_mutex_destroy(&data->write);
	pthread_mutex_destroy(&data->arbitrator2);
	free_function(data);
}



int	main(int argc, char *argv[])
{
	t_data	data;

	data.start_time = gettime() + 1000;
	argv[1] = "5";
	argv[2] = "400";
	argv[3] = "100";
	argv[4] = "100";
	argv[5] = "2";
	argc = 6;
	if (init(&data, argc, argv) != 0)
		exit_programm("not enough, too many or wrong arguments");
	if (check(data) != 0)
		return 0;
	threads(&data);
	return 0;
}
