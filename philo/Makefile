PHILO = philo

SRC_DIR = src
INCLUDE_DIR = include
OBJS_DIR = objs

FILES = philo.c		\
	mutexs/factory.c	\
	mutexs/locker.c	\
	life/death.c	\
	life/eat.c	\
	life/forks.c	\
	life/look.c	\
	life/sleep.c	\
	life/think.c	\
	initializer.c	\
	destructor.c	\
	checkers/args.c	\
	checkers/death.c	\
	checkers/meals.c	\
	simulation.c	\
	utils/time.c	\
	utils/display.c	\
	utils/error.c	\
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
