# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: meserghi <meserghi@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/12 18:29:15 by meserghi          #+#    #+#              #
#    Updated: 2024/03/15 01:09:24 by meserghi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

FILE = philo_bonus.c utils/ft_atoi_bonus.c utils/init_philo_bonus.c utils/parsing_bonus.c\
	utils/my_time_bonus.c utils/my_sleep_bonus.c utils/routine_bonus.c utils/my_free_bonus.c
#utils/my_free_bonus.c
FILE_OBJ = ${FILE:.c=.o}
#-fsanitize=thread -g
FLAGS = -Wall -Wextra -Werror #-fsanitize=thread -g
NAME = philo_bonus

all : ${NAME}

${NAME} : ${FILE_OBJ}
	gcc ${FLAGS} ${FILE_OBJ} -o ${NAME}

%.o : %.c philo_bonus.h
	gcc ${FLAGS} -c $< -o $@

clean :
	rm -f ${FILE_OBJ}

fclean : clean
	rm -f ${NAME}

re : fclean all