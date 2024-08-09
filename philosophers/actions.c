#include "philo.h"

void take_forks(t_philo *philo)
{
	int l;
	int r;


	l = philo->id - 1;
	r = philo->id % philo->numphilo;
	if (pthread_mutex_lock(&philo->data->arbitrator2) != 0)
		perror("arbitrator lock");
	if (l < r)
	{
		if (pthread_mutex_lock(&philo->data->forks[l]) != 0)
			perror("fork lock l");
		write_message("takes left fork", philo);
		if(pthread_mutex_lock(&philo->data->forks[r]) != 0)
			perror("fork lock r");
		write_message("takes right fork", philo);
	}
	else
	{
		if(pthread_mutex_lock(&philo->data->forks[r]) != 0)
			perror("fork lock r");
		write_message("takes right fork", philo);
		if (pthread_mutex_lock(&philo->data->forks[l]) != 0)
			perror("fork lock l");
		write_message("takes left fork", philo);
	}
	if (pthread_mutex_unlock(&philo->data->arbitrator2) != 0)
		perror("arbitartor unlock");
}



void eating(t_philo *philo)
{
	philo->start_eat = gettime();
    write_message("eats", philo);
    while (gettime() < philo->start_eat + philo->time_to_eat)
        usleep(100);
	philo->last_time_eat = gettime();
}

void drop_forks(t_philo *philo)
{
	int l;
	int r;


	l = philo->id - 1;
	r = philo->id % philo->numphilo;
	if (l > r)
	{
		if (pthread_mutex_unlock(&philo->data->forks[l]) != 0)
			perror("fork unlock l");
		write_message("dropped left fork", philo);
		if(pthread_mutex_unlock(&philo->data->forks[r]) != 0)
			perror("fork unlock r");
		write_message("dropped right fork", philo);
	}
	else
	{
		if(pthread_mutex_unlock(&philo->data->forks[r]) != 0)
			perror("fork unlock r");
		write_message("dropped right fork", philo);
		if (pthread_mutex_unlock(&philo->data->forks[l]) != 0)
			perror("fork unlock l");
		write_message("dropped left fork", philo);
	}
}