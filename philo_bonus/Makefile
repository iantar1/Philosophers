NAME = philo_bonus

SRCS = philosophers_bonus.c utils_parcing_bonus.c parce_bonus.c ft_itoa.c ft_printf.c utils2.c utils3.c

OBJS = ${SRCS:.c=.o}

CFLAGS = -Wall -Wextra -Werror

${NAME}:${OBJS}
	cc ${CFLAGS} ${OBJS} -o ${NAME}

all:${NAME}
	

clean:
	rm -rf ${OBJS}

fclean: clean
	rm -rf ${NAME}

re: fclean all