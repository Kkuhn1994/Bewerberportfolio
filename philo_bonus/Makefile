all: philo

NAME = philo
FLAGS = -Wall -Wextra -Werror -g -pthread
PROJECTFILES = philo.c action.c utils.c init.c utils2.c utils3.c utils4.c
philo: ${PROJECTFILES}
	cc ${PROJECTFILES} ${CFLAGS} -o philo_bonus

clean:
	rm -rf ./philo_bonus

fclean:
	rm -rf ./philo_bonus

re:
	make fclean
	make all