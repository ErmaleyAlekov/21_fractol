SOURCES = f.c main.c utils.c\

FLAGS = -Wall -Werror -Wextra -lmlx -framework OpenGL -framework AppKit -o fractol
NAME = fractol
OBJECT = $(SOURCES:%.c=%.o)
GREEN ='\033[0;32m'
RED ='\033[0;31m'
all: $(NAME)
$(NAME) : $(OBJECT) f.h
	@gcc $(FLAGS) $(SOURCES)
	@echo "$(GREEN)Compiling code ---->>>> $(OBJECT) OK"
	@echo "$(GREEN)fractol greated!"

clean:
	@echo "$(RED)Delete objects !"
	@rm -f -v $(OBJECT) 
fclean:
	@echo "$(RED)Delete All!"
	@rm -f -v $(NAME) $(OBJECT)
re: fclean all

.PHONY: all clean fclean re del test