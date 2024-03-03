
FILE = philo.c utils/ft_atoi.c utils/parsing.c utils/my_time.c

FILE_OBJ = ${FILE:.c=.o}

FLAGS = -Wall -Wextra -Werror

NAME = philo

all : ${NAME}
 
${NAME} : ${FILE_OBJ}
	gcc ${FLAGS} ${FILE_OBJ} -o ${NAME}

%.o : %.c philo.h
	gcc ${FLAGS} -c $< -o $@

clean :
	rm -f ${FILE_OBJ}

fclean : clean
	rm -f ${NAME}

re : fclean all