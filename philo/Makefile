# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ilopez-r <ilopez-r@student.42malaga.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/23 16:35:38 by ilopez-r          #+#    #+#              #
#    Updated: 2024/04/26 15:49:25 by ilopez-r         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

FLAGS = -Wall -Werror -Wextra

FILES = philo.c\
		waiter.c\
		routine.c\
		utils.c\
		
OBJS = $(FILES:.c=.o)

all : $(NAME)

$(NAME) : $(OBJS)
	@gcc $(FLAGS) $(FILES)  -o $(NAME)

$(OBJS) : $(FILES)
	@gcc $(FLAGS) -c $< -o $@

clean:
	@rm -fr $(OBJS)

fclean: clean
	@rm -fr $(NAME)

re: fclean all

.PHONY : all clean fclean re