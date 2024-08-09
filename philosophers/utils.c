#include "philo.h"

void exit_programm(char *errormessage)
{
	ft_putstr_fd(errormessage, 2);
	exit(1);
}

void write_message(char *action, t_philo *philo)
{
	char *time;
	char *id_string;

	// FILE *file = fopen("philosopher_log.txt", "a"); // Change the file name as needed
    // if (file == NULL) {
    //     perror("Error opening file");
    //     return;
    // }

    // Print initialization information to the file
    // fprintf(file, "Philosopher %d initialized:\n", philo->id);
    // fprintf(file, "  Left Fork Address: %p\n", (void*)philo->l);
    // fprintf(file, "  Right Fork Address: %p\n", (void*)philo->r);
    // fprintf(file, "  Start Time: %ld\n", philo->start_time);
    // fprintf(file, "  Time to Die: %ld\n", philo->time_to_die);
    // fprintf(file, "  Time to Eat: %ld\n", philo->time_to_eat);
    // fprintf(file, "  Time to Sleep: %ld\n", philo->time_to_sleep);
    // fprintf(file, "  Number of Meals: %li\n", philo->num_meals);
    // fprintf(file, "  Data Pointer: %p\n\n", (void*)philo->data);	
	// fclose(file);
	pthread_mutex_lock(&philo->data->write);
	pthread_mutex_lock(&philo->arbitrator);
	ft_putstr_fd("philo", 1);
	ft_putstr_fd(" ", 1);
	id_string = ft_itoa(philo->id);
	ft_putstr_fd(id_string, 1);
	free(id_string);
	ft_putstr_fd(" ", 1);
	ft_putnbr_fd((int)(gettime() - philo->start_time), 1);
	ft_putstr_fd(" ", 1);
	ft_putstr_fd(action, 1);
	ft_putstr_fd("\n", 1);
	pthread_mutex_unlock(&philo->arbitrator);
	pthread_mutex_unlock(&philo->data->write);
}


time_t	gettime(void)
{
	struct		timeval tv;
	time_t		time;

	gettimeofday(&tv, NULL);
	time = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	return (time);
}

void	free_function(t_data *data)
{
	free(data->forks);
	free(data->philos);
	free(data->threads);
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

