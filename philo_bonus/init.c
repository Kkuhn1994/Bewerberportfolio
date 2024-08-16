/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkuhn <kkuhn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 18:08:58 by kkuhn             #+#    #+#             */
/*   Updated: 2024/08/15 18:50:33 by kkuhn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	check_argument_valid(int argc, char *argv[])
{
	int	i;
	int	j;

	i = 0;
	while (++ i < argc)
	{
		j = -1;
		while (argv[i][++ j] != 0)
			if (ft_isdigit((int)argv[i][j]) == 0)
				exit_programm("argument is invalid");
	}
	return (0);
}

int	init(t_data *data, int argc, char *argv[])
{
	if (argc < 5 || argc > 6)
		return (1);
	check_argument_valid(argc, argv);
	data->finished = 0;
	data->i = 0;
	data->num_philo = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		data->num_meals = ft_atoi(argv[5]);
	else
		data->num_meals = -1;
	return (0);
}

void	init_philos(t_data *data)
{
	data->philos->numphilo = data->num_philo;
	data->philos->start_time = data->start_time;
	data->philos->time_to_die = data->time_to_die;
	data->philos->time_to_eat = data->time_to_eat;
	data->philos->time_to_sleep = data->time_to_sleep;
	data->philos->num_meals = data->num_meals;
	data->philos->id = 1;
	data->philos->data = data;
	data->philos->start_eat = data->philos->start_time;
	data->philos->philo_died = 0;
	data->philos->nrmeals = 0;
	data->philos->finished = 0;
}

void	init2(t_data *data)
{
	sem_unlink("/fork");
	sem_unlink("/kill");
	sem_unlink("/arbitrator");
	sem_unlink("/write");
	data->forks = sem_open("/fork", O_CREAT, 0644, data->num_philo);
	data->arbitrator = sem_open("/arbitrator", O_CREAT, 0644, 1);
	data->write = sem_open("/write", O_CREAT, 0644, 1);
	data->kill = sem_open("/kill", O_CREAT, 0644, 0);
	data->processes = malloc(data->num_philo * sizeof(pid_t));
}
