/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkuhn <kkuhn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 14:05:36 by kkuhn             #+#    #+#             */
/*   Updated: 2024/08/15 18:48:16 by kkuhn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <sys/wait.h>
# include "semaphore.h"
# include <signal.h>
# include <fcntl.h>
# include <limits.h>
# define COLOR_RED		"\033[31m"
# define COLOR_GREEN	"\033[32m"
# define COLOR_YELLOW	"\033[33m"
# define COLOR_BLUE		"\033[34m"
# define COLOR_MAGENTA	"\033[35m"
# define COLOR_CYAN		"\033[36m"
# define COLOR_RESET	"\033[0m"

typedef struct s_data	t_data;

typedef struct philo_t{
	t_data			*data;
	int				id;
	size_t			num_meals;
	time_t			time_to_die;
	time_t			time_to_eat;
	time_t			time_to_think;
	time_t			time_to_sleep;
	time_t			start_eat;
	time_t			start_sleep;
	time_t			start_think;
	time_t			start_time;
	int				numphilo;
	int				philo_died;
	int				nrmeals;
	int				finished;
	sem_t			*death;
	pthread_t		monitor_thread;
}	t_philo;

typedef struct s_data {
	size_t			num_philo;
	time_t			time_to_die;
	time_t			time_to_eat;
	time_t			time_to_sleep;
	time_t			start_time;
	size_t			num_meals;
	t_philo			philos[1];
	sem_t			*forks;
	sem_t			*arbitrator;
	sem_t			*write;
	sem_t			*kill;
	pid_t			*processes;
	int				finished;
	int				i;
	pthread_t		monitor_thread;	
}	t_data;

void	sleeptime(t_philo *philo);
void	think(t_philo *philo);
void	take_forks(t_philo *philo);
void	eating(t_philo *philo);
void	drop_forks(t_philo *philo);
int		check_argument_valid(int argc, char *argv[]);
int		init(t_data *data, int argc, char *argv[]);
void	init_philos(t_data *data);
void	write_message(char *action, t_philo *philo, char *color);
time_t	gettime(void);
void	exit_programm(char *errormessage);
int		check(t_data *data);
void	init2(t_data *data);
void	*kill_process(void *input);
void	*single_philo(void *input);
void	ft_putstr_fd(char *s, int fd);
void	ft_putnbr_fd(int number, int fd);
size_t	ft_strlen(char const *str);
size_t	ft_strlcpy(char *dst, char *src, size_t dstsize);
char	*ft_itoa(int n);
int		ft_atoi(const char *number);
int		ft_isdigit(int a);
void	close_sem(t_data *data);

#endif 