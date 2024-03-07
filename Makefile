# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: meserghi <meserghi@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/07 18:22:05 by meserghi          #+#    #+#              #
#    Updated: 2024/03/07 21:23:38 by meserghi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

FILE = philo.c utils/ft_atoi.c utils/init_philo.c utils/parsing.c utils/my_time.c utils/my_free.c

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