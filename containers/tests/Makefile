NAME = ft_containers

FILES = deque_check.cpp list_check.cpp map_check.cpp \
		queue_check.cpp stack_check.cpp vector_check.cpp main.cpp

.PHONY:	all clean fclean re

all: $(NAME)

$(NAME): $(FILES)
	clang++ -Wall -Wextra -Werror $(FILES) -o $(NAME)

clean:
	@echo "There is no trash here"
	
fclean:
	rm -f $(NAME)
	
re: fclean all
