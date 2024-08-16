NAME = philo

CC = @cc
CFLAGS = -Wall -Werror -Wextra -pthread -g3
AR = ar
ARFLAGS = rcs

SRCS_FILES = main.c parsing.c utils.c init.c \

OBJ_FILES = $(patsubst %.c, %.o, $(SRC_FILES))

all : $(NAME)

$(NAME): $(OBJ_FILES)
	@$(AR) $(ARFLAGS) $(NAME) $(OBJ_FILES)
	@echo "\033[32mphilo compiled\033[0m"

clean:
	@rm -rf $(OBJDIR)
	@echo "\033[31mclean philo\033[0m"

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re bonus