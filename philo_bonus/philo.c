/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkuhn <kkuhn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 18:06:33 by kkuhn             #+#    #+#             */
/*   Updated: 2024/08/15 20:41:10 by kkuhn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	*kill_process(void *input)
{
	size_t	i;
	t_data	*data;

	i = 0;
	data = input;
	sem_wait(data->kill);
	while (i < data->num_philo)
	{
		kill(data->processes[i], SIGTERM);
		waitpid(data->processes[i], NULL, 0);
		i ++;
	}
	return (NULL);
}

void	*monitor_thread(void *input)
{
	t_philo	*philo;
	int		finished;
	size_t	i;

	i = 0;
	finished = 0;
	philo = input;
	while (finished == 0)
	{
		if (gettime() - philo->start_eat > philo->time_to_die)
		{
			sem_post(philo->data->kill);
			write_message("died", philo, COLOR_RED);
			return (NULL);
		}
		sem_wait(philo->death);
		finished = philo->finished;
		sem_post(philo->death);
	}
	return (NULL);
}

void	philo_process(t_philo *philo)
{
	while (gettime() < philo->start_time)
		usleep(100);
	if (philo->id % 2 == 0)
		think(philo);
	while (philo->num_meals > philo->nrmeals)
	{
		take_forks(philo);
		eating(philo);
		drop_forks(philo);
		sleeptime(philo);
		think(philo);
		philo->nrmeals++;
	}
	sem_wait(philo->death);
	philo->finished = 1;
	sem_post(philo->death);
	pthread_join(philo->monitor_thread, 0);
	return ;
}

void	process_start(t_data *data)
{
	size_t		i;
	pthread_t	monitor;

	i = -1;
	init2(data);
	sem_unlink("/death");
	data->philos->death = sem_open("/death", O_CREAT, 0644, 1);
	pthread_create(&data->philos->monitor_thread, 0, &monitor_thread, &data->philos);
	pthread_detach(data->philos->monitor_thread);
	pthread_create(&monitor, 0, &kill_process, data);
	pthread_detach(monitor);
	while (++ i < data->num_philo)
	{
		data->processes[i] = fork();
		if (data->processes[i] == -1)
			exit_programm("fork failed");
		if (data->processes[i] == 0)
			philo_process(data->philos);
		data->philos->id ++;
	}
	i = -1;
	while (++ i < data->num_philo)
		waitpid(data->processes[i], NULL, 0);
	sem_post(data->kill);
	sem_close(data->philos->death);
	sem_unlink("/death");
	close_sem(data);
}

int	main(int argc, char *argv[])
{
	t_data	data;

	data.start_time = gettime() + 1000;
	if (init(&data, argc, argv) != 0)
		exit_programm("not enough, too many or wrong arguments");
	if (check(&data) != 0)
		return (0);
	init_philos(&data);
	process_start(&data);
	free(data.processes);
	return (0);
}
