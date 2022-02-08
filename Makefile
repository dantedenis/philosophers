###### MAIN ATTRIBUTES #####

NAME = philo
CC = clang
FLAGS = -Wextra -Wall -Werror -g

###### SOURCE FILES #####

OBJ_PATH = ./bin/
SRC_PATH = ./src/

SRC_LST = main.c	utils.c	action.c	init.c	

SRC = $(addprefix $(SRC_PATH), $(SRC_LST))

###### HEADERS FILES #####

HEADERS = ./inc/philosophers.h

###### OBJECT FILES #####

OBJ		= $(addprefix $(OBJ_PATH), $(patsubst %.c,%.o,$(SRC_LST)))

.PHONY : all clean fclean re

all : $(OBJ_PATH) $(NAME)

$(OBJ_PATH):
	mkdir -p $(OBJ_PATH)

$(NAME) : $(OBJ)
	$(CC) $(OBJ) -o $@

$(OBJ_PATH)%.o : $(SRC_PATH)%.c $(HEADERS)
	$(CC) $(FLAGS) -I ./inc -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -rf $(NAME)

re: fclean all
