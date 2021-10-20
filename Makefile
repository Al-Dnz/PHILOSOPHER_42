NAME = philo
SRC =	main.c \
		philo_util.c \
		philo_routine.c \
		time_handler.c \
		lib_util.c \

INC = inc
OBJ_DIR = obj
SRC_DIR = src
CC = clang
CFLAGS = -Wall -Werror -Wextra
OBJ = $(addprefix $(OBJ_DIR)/,$(SRC:.c=.o))

all:
	@mkdir -p $(OBJ_DIR)
	@$(MAKE) -s $(NAME)

$(NAME): $(OBJ)
	${CC} $(CFLAGS) $(OBJ) -I $(INC) -o $(NAME) -lpthread
	@echo "\033[0;32m------------------------------\033[0m"
	@echo "\033[0;32m| => $(NAME) well created ! <= |\033[0m"
	@echo "\033[0;32m------------------------------\033[0m"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c 
	${CC} $(CFLAGS) -I $(INC) -c $< -o $@

clean:
	@rm -rf $(OBJ_DIR)
	@echo "\033[0;31m=> obj deleted <=\033[0m"

fclean:	clean
	@rm -rf $(NAME)
	@echo "\033[0;31m=> $(NAME) deleted <=\033[0m"

re: fclean all

.PHONY: all, clean, fclean, re
