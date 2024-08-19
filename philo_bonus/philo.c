/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kevin <kevin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 18:06:33 by kkuhn             #+#    #+#             */
/*   Updated: 2024/08/18 23:48:40 by kevin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void *kill_process(t_data *data)
{
	size_t i;

	i = 0;
	printf("tets");
	while (i < data->num_philo)
	{
		kill(data->processes[i], SIGTERM);
		waitpid(data->processes[i], NULL, 0);
		i++;
	}
	return (NULL);
}

void *monitor_thread(void *input)
{
	t_philo *philo;
	int finished;
	size_t i;

	i = 0;
	finished = 0;
	philo = input;
	while (1)
	{

		// ft_putnbr_fd((int)philo->time_to_eat, 2);
		// ft_putstr_fd("\n", 2);
		if (gettime() - philo->start_eat > philo->time_to_die)
		{
			write_message("died", philo, COLOR_RED);
			exit(1);
		}
		// sem_wait(philo->death);
		// finished = philo->finished;
		// sem_post(philo->death);
	}
	return (NULL);
}

void philo_process(t_philo *philo)
{

	// ft_putnbr_fd((int)philo->time_to_die, 2);
	// ft_putstr_fd("\n", 2);
	pthread_create(&philo->monitor_thread, 0, &monitor_thread, philo);
	pthread_detach(philo->monitor_thread);
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
	exit(0);
}

void process_start(t_data *data)
{
	size_t i;
	pthread_t monitor;

	i = -1;
	init2(data);
	sem_unlink("/death");
	data->philos->death = sem_open("/death", O_CREAT, 0644, 1);

	// pthread_create(&monitor, 0, &kill_process, data);
	while (++i < data->num_philo)
	{
		data->processes[i] = fork();
		if (data->processes[i] == -1)
			exit_programm("fork failed");
		if (data->processes[i] == 0)
			philo_process(data->philos);
		if (i != data->num_philo - 1)
			data->philos->id++;
	}
	i = -1;
	int status;
	while (++i < data->num_philo)
	{
		waitpid(-1, &status, 0);
		if (WEXITSTATUS(status) == 1)
			kill_process(data);
	}
	sem_close(data->philos->death);
	sem_unlink("/death");
	close_sem(data);
}

int main(int argc, char *argv[])
{
	t_data data;

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
