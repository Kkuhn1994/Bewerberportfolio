#ifndef PHILO_H
#define PHILO_H


#include <stdlib.h>
#include <stdio.h> 
#include <pthread.h>
#include "libft/libft.h"

#define TAKE_FORKS "takes fork"
#define EATS "eats"

typedef struct s_data t_data;

typedef struct {
	t_data *data;
	int id;
	size_t num_meals;
	time_t time_to_die;
	time_t time_to_eat;
	time_t time_to_sleep;
	time_t start_time;	
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
	pthread_mutex_t *write;
	pthread_mutex_t arbitrator2;
	pthread_t *threads;
} t_data;


void exit_programm(char *errormessage);

#endif 