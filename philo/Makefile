NAME = philo

SRCS = philosophers.c utils_parcing.c parce.c utils2.c ft_printf.c philo_utils1.c

OBJS = ${SRCS:.c=.o}

CFLAGS = -Wall -Wextra -Werror #-fsanitize=thread -fsanitize=address

${NAME}:${OBJS}
	cc ${CFLAGS} ${OBJS} -o ${NAME}

all:${NAME}
	

clean:
	rm -rf ${OBJS}

fclean: clean
	rm -rf ${NAME}

re: fclean all