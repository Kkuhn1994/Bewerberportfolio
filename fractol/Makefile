NAME = fractol
CFLAGS = -Wall -Wextra -Werror -O3
OBJECTS = libft/ft_toupper.o \
       libft/ft_tolower.o \
       libft/ft_substr.o \
       libft/ft_strtrim.o \
       libft/ft_strrchr.o \
       libft/ft_strnstr.o \
       libft/ft_strncmp.o \
       libft/ft_strmapi.o \
       libft/ft_strlen.o \
       libft/ft_strlcpy.o \
       libft/ft_strlcat.o \
       libft/ft_strjoin.o \
       libft/ft_striteri.o \
       libft/ft_strdup.o \
       libft/ft_strchr.o \
       libft/ft_split.o \
       libft/ft_putstr_fd.o \
       libft/ft_putnbr_fd.o \
       libft/ft_putendl_fd.o \
       libft/ft_putchar_fd.o \
       libft/ft_memset.o \
       libft/ft_memmove.o \
       libft/ft_memcpy.o \
       libft/ft_memcmp.o \
       libft/ft_memchr.o \
       libft/ft_lstsize_bonus.o \
       libft/ft_lstnew_bonus.o \
       libft/ft_lstmap_bonus.o \
       libft/ft_lstlast_bonus.o \
       libft/ft_lstiter_bonus.o \
       libft/ft_lstdelone_bonus.o \
       libft/ft_lstclear_bonus.o \
       libft/ft_lstadd_front_bonus.o \
       libft/ft_lstadd_back_bonus.o \
       libft/ft_itoa.o \
       libft/ft_isprint.o \
       libft/ft_isdigit.o \
       libft/ft_isascii.o \
       libft/ft_isalpha.o \
       libft/ft_isalnum.o \
       libft/ft_calloc.o \
       libft/ft_bzero.o \
       libft/ft_atoi.o \

FRACTOL = is_julia.o is_mandelbrot.o complex_calc.o fractal_gen.o newton.o \
       utils.o utils2.o

OBJ = $(OBJECTS:.o=.c)

LIBS = -L./minilibx -lmlx -framework OpenGL -framework AppKit

all: fractol

fractol: main.o ${FRACTOL} ${OBJECTS} minilibx/libmlx.a
	gcc ${CFLAGS} -o $@ $^ $(LIBS)

main.o: main.c
	gcc -c ${CFLAGS} $< -o $@

%.o: %.c
	gcc -c $(CFLAGS) -o $@ $^

${OBJECTS}:	${OBJ}
	make -C ./libft
	make bonus -C ./libft

minilibx/libmlx.a:
	make -C ./minilibx

clean:
	make clean -C ./minilibx
	make clean -C ./libft 
	rm -f ${OBJECTS} *.o

fclean:
	make fclean -C ./libft
	make clean
	rm -f ${OBJECTS} ${NAME}

re:	fclean all