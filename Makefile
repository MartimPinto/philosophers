# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mcarneir <mcarneir@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/20 12:40:52 by mcarneir          #+#    #+#              #
#    Updated: 2023/10/11 15:31:33 by mcarneir         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror -pthread -g -fsanitize=thread
#CFLAGS = -g -Wall -Wextra -Werror -lpthread -g3 -fsanitize=thread -O3 -march=native
RM = rm -fr

NAME = philo

SRC =	src/main.c \
		src/parser.c \
		src/utils.c \
		src/free.c \
		src/init.c \
		src/check.c \
		src/actions.c \

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
		$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

clean:
		@$(RM) $(OBJ)

fclean: clean
		@$(RM) $(NAME)

re: fclean all