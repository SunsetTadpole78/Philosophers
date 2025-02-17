PHILO = philo

SRC_DIR = src
INCLUDE_DIR = include
OBJS_DIR = objs

FILES = philo.c		\
	mutex_manager.c	\
	initializer.c	\
	destructor.c	\
	args_checker.c	\
	game.c	\
	utils/ft_atoi.c	\
	utils/ft_is_uint.c	\
	utils/ft_realloc.c	\
	utils/ft_strlen.c

OBJS = $(FILES:%.c=$(OBJS_DIR)/%.o)

FLAGS = -Wall -Werror -Wextra -g

all: $(PHILO)

$(PHILO): $(OBJS)
	cc $(FLAGS) $(OBJS) -o $(PHILO) -I $(INCLUDE_DIR)

$(OBJS_DIR)/%.o: $(SRC_DIR)/%.c
	mkdir -p $(dir $@)
	cc $(FLAGS) $< -c -o $@ -I $(INCLUDE_DIR)

clean:
	rm -f $(OBJS)
	rm -rf $(OBJS_DIR)

fclean: clean
	rm -f $(PHILO)

re: fclean all

.PHONY: all clean fclean re
