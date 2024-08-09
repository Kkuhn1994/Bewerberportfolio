#include "philo.h"

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

void	init_threads(t_data *data)
{
	int	i;

	i = 0;
	data->forks = malloc ((data->num_philo) * sizeof(pthread_mutex_t));
	data->threads = malloc ((data->num_philo + 1) * sizeof(pthread_t));
	data->philos = malloc ((data->num_philo) * sizeof(t_philo));
	data->philos[data->num_philo - 1].r = &data->forks[0];
	while (i < data->num_philo)
	{
		data->philos[i].numphilo = data->num_philo;
		data->philos[i].l = &data->forks[i];
		if (i != data->num_philo - 1)
			data->philos[i].r = &data->forks[i + 1];
		data->philos[i].start_time = data->start_time;
		data->philos[i].time_to_die = data->time_to_die;
		data->philos[i].time_to_eat = data->time_to_eat;
		data->philos[i].time_to_sleep = data->time_to_sleep;
		data->philos[i].num_meals = data->num_meals;
		data->philos[i].id = i + 1;
		data->philos[i].data = data;
		data->philos[i].last_time_eat = data->philos[i].start_time;
		data->philos[i].philo_died = 0;
		data->philos[i].nrmeals = 0;
        // printf("Philosopher %d initialized:\n", data->philos[i].id);
        // printf("  Left Fork Address: %p\n", (void*)data->philos[i].l);
        // printf("  Right Fork Address: %p\n", (void*)data->philos[i].r);
        // printf("  Start Time: %ld\n", data->philos[i].start_time);
        // printf("  Time to Die: %ld\n", data->philos[i].time_to_die);
        // printf("  Time to Eat: %ld\n", data->philos[i].time_to_eat);
        // printf("  Time to Sleep: %ld\n", data->philos[i].time_to_sleep);
        // printf("  Number of Meals: %li\n", data->philos[i].num_meals);
        // printf("  Data Pointer: %p\n\n", (void*)data->philos[i].data);		
		i ++;
	}
}