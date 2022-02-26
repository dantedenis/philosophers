###### MAIN ATTRIBUTES #####

NAME	= philo_bonus
CC		= gcc
FLAGS	= -Wextra -Wall -Werror -pthread -g
HEADERS	= ./inc/philosophers_bonus.h

###### SOURCE FILES #####

SRC_PATH	=	./src/
SRC_LIST	=	main_bonus.c		utils_bonus.c		action_bonus.c\
				init_bonus.c		routing_bonus.c

###### OBJECT FILES #####

OBJ_PATH	= ./bin/
OBJ			= $(addprefix $(OBJ_PATH), $(patsubst %.c, %.o, $(SRC_LIST)))

###### BUILDER #####

.PHONY : all clean fclean re

all : $(OBJ_PATH) $(NAME)

$(OBJ_PATH):
	mkdir $(OBJ_PATH)

$(NAME) : $(OBJ)
	$(CC) $(OBJ) -o $@

$(OBJ_PATH)%.o : $(SRC_PATH)%.c $(HEADERS)
	$(CC) $(FLAGS) -I ./inc -c $< -o $@

clean:
	rm -rf $(OBJ_PATH)

fclean: clean
	rm -rf $(NAME)

re: fclean all
