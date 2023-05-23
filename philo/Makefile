NAME = philo

SRCS = new_philosophers.c utils_parcing.c parce.c

OBJS = ${SRCS:.c=.o}

CFLAGS = -Wall -Wextra -Werror -fsanitize=thread

${NAME}:${OBJS}
	cc ${CFLAGS} ${OBJS} -o ${NAME}

all:${NAME}
	

clean:
	rm -rf ${OBJS}

fclean: clean
	rm -rf ${NAME}

re: fclean all