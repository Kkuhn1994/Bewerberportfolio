#include "philo.h"


void exit_programm(char *errormessage)
{
	ft_putstr_fd(errormessage, 2);
	exit(1);
}