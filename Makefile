SRCS = ${wildcard  ./src/*.c} ${wildcard  ./src/**/*.c}

OBJS = ${SRCS:%.c=%.o}

CC = cc

INCLUDES = -I./ -I./src

FLAGS = -Wall -Wextra ${INCLUDES} -pthread #-fsanitize=thread

NAME = philo

%.o : %.c
	@$(CC) $(FLAGS) -c $^ -o $@

all : $(NAME)

WHITE_TEXT = \033[1;37m
RED_TEXT = \033[0;31m
NC_TEXT = \033[0m
GREEN_TEXT= \033[0;32m

$(NAME) : $(OBJS) 
	@echo "$(WHITE_TEXT)Compiling Binary..."
	@$(CC) $(FLAGS) $^ -o $(NAME)
	@echo "$(GREEN_TEXT)	Success : $(NAME) Compiled Successfully"
	@echo "$(WHITE_TEXT)Finished"
	@echo "$(NC_TEXT)"

clean :
	@echo "$(RED_TEXT)Cleaning $(NAME) Object Files"
	@rm -rf	$(OBJS)
	@echo "$(NC_TEXT)"

fclean : clean
	@echo "$(RED_TEXT)Cleaning $(NAME) Binaries"
	@rm -rf $(NAME)
	@echo "$(NC_TEXT)"

re : fclean all

.PHONY: clean fclean re all