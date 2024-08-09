#ifndef PHILO_H
#define PHILO_H


#include <stdlib.h>
#include <stdio.h> 
#include <pthread.h>
#include "libft/libft.h"
#include <fcntl.h>
#include <sys/time.h>

#define TAKE_FORKS "takes fork"
#define EATS "eats"

typedef struct s_data t_data;

typedef struct {
	t_data *data;
	int id;
	size_t num_meals;
	time_t time_to_die;
	time_t time_to_eat;
	time_t start_eat;
	time_t last_time_eat;
	time_t time_to_sleep;
	time_t start_time;
	int numphilo;
	int philo_died;
	int nrmeals;
	pthread_mutex_t *l;
	pthread_mutex_t *r;
	pthread_mutex_t arbitrator;
	pthread_t instructor;
}	t_philo;

typedef struct s_data {
	size_t num_philo;
	time_t time_to_die;
	time_t time_to_eat;
	time_t time_to_sleep;
	time_t start_time;
	size_t num_meals;
	t_philo *philos;
	pthread_mutex_t *forks;
	pthread_mutex_t write;
	pthread_mutex_t arbitrator2;
	pthread_t *threads;
	int finished;
	int i;
} t_data;


void	exit_programm(char *errormessage);
void 	free_function(t_data *data);
time_t	gettime(void);
void	write_message(char *action, t_philo *philo);
int		init(t_data *data, int argc, char *argv[]);
void	init_threads(t_data *data);
int		check(t_data data);
void	take_forks(t_philo *philo);
void	eating(t_philo *philo);
void	drop_forks(t_philo *philo);

#endif 