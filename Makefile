# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: uterese <uterese@student.21-school.ru>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/27 19:28:27 by uterese           #+#    #+#              #
#    Updated: 2021/11/27 19:28:32 by uterese          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fractol

CC = gcc

HEADERS_PATH = ./includes/

INCLUDES = -I$(HEADERS_PATH) 

CFLAGS = -Wall -Wextra -Werror -g3
RM = rm -rf

DIR = $(shell pwd)

DIRSRC = sources

GREEN ='\033[0;32m'
RED ='\033[0;31m'

MLX_OPENGL_PATH = ./minilibx_opengl
MLX_LINUX_PATH = ./minilibx_linux
MLX_WINDOWS_PATH = ./minilibx_windows

MLX_PATH = 

FRAMEWORKS = 

LINKS = 

UNAME = $(shell uname)

ifeq ($(UNAME),Darwin)
	MLX_PATH = $(MLX_OPENGL_PATH)
	MLX_NAME = libmlx.a
	MLX_LIB = $(MLX_PATH)/$(MLX_NAME)
	LINKS = -L$(MLX_PATH)/
	FRAMEWORKS += -framework OpenGL -framework Appkit
	INCLUDES += -I$(MLX_OPENGL_PATH)
	LOAD_DYLIB = install_name_tool -change $(MLX_NAME) $(DIR)/$(MLX_LIB) $(NAME)
	SRC = $(addprefix $(DIRSRC)/, \
			f.c main.c utils.c)
endif

ifeq ($(UNAME),Linux)
	MLX_PATH = $(MLX_LINUX_PATH)
	MLX_NAME = libmlx.a
	INCLUDES += -I$(MLX_LINUX_PATH)
	LINKS += -L$(MLX_PATH) -lXext -lX11 -lxcb -lXau -lXdmcp -lm
	MLX_LIB = $(MLX_PATH)/$(MLX_NAME)
	SRC = $(addprefix $(DIRSRC)/, \
			f.c main.c utils.c)
endif

ifeq ($(OS),Windows_NT)
	MLX_PATH = $(MLX_WINDOWS_PATH)
	MLX_NAME = libmlx.a
	MLX_LIB = $(MLX_PATH)/$(MLX_NAME)
	LINKS = -L"$(MLX_PATH)/SDL/lib" -lmingw32 -lSDL2main -lSDL2 -lSDL2_image \
	-lSDL2_mixer -lSDL2_ttf  -lmingw32 -lSDL2main -luser32 -lgdi32 -lwinmm -ldxguid
	INCLUDES += -I$(MLX_WINDOWS_PATH)/includes
	LOAD_DYLIB = cp $(MLX_PATH)/*.dll ../
	SRC = $(addprefix $(DIRSRC)/, \
			f.c main.c utils.c)
endif

OBJDIR = obj

OBJ = $(SRC:$(DIRSRC)/%.c= $(OBJDIR)/%.o)

OBJ_PATHS = $(OBJDIR) $(shell ls -R $(DIRSRC) | grep / | sed 's/://g' | sed 's/src/$(OBJDIR)/g')

HEADERS = $(addprefix $(HEADERS_PATH), \
 f.h)

all: $(NAME) $(HEADERS)
	
$(NAME): $(MLX_LIB) $(OBJ)
	
	@$(CC) $(CFLAGS) $(INCLUDES) $(OBJ) $(MLX_LIB) -o $(NAME) $(LINKS) $(FRAMEWORKS)
	@$(LOAD_DYLIB)
	@echo "$(GREEN)______________________________________________________"
	@echo "$(GREEN)~####~~##~~##~~####~~~####~~#####~~~####~~~####~~~~###"
	@echo "$(GREEN)##~~~~~##~~##~##~~##~##~~##~##~~~~~##~~~~~##~~~~~~~###"
	@echo "$(GREEN)~####~~##~~##~##~~~~~##~~~~~####~~~~####~~~####~~~~###"
	@echo "$(GREEN)~~~~##~##~~##~##~~##~##~~##~##~~~~~~~~~##~~~~~##"
	@echo "$(GREEN)~####~~~####~~~####~~~####~~#####~~~####~~~####~~~~###"
	@echo "$(GREEN)______________________________________________________"

$(MLX_LIB):
	@echo "COMPILING MLX"
	@$(MAKE) -C $(MLX_PATH)/

$(OBJDIR)/%.o: $(DIRSRC)/%.c $(WAIT) $(HEADERS) $(MLX_LIB) 
	@mkdir -p $(OBJ_PATHS)
	@$(CC) $(CFLAGS) $(INCLUDES) -c -o $@ $< 
clean:
	@echo "$(RED)_______________________________________________________________________"
	@echo "$(RED)#####~~#####~~##~~~~~#####~~######~#####  ~####~~#####~~######~~~~~~###"
	@echo "$(RED)##~~##~##~~~~~##~~~~~##~~~~~~~##~~~##     ##~~##~##~~##~~~~~##~~~~~~###"
	@echo "$(RED)##~~##~####~~~##~~~~~####~~~~~##~~~####   ##~~##~#####~~~~~~##~~~~~~###"
	@echo "$(RED)##~~##~##~~~~~##~~~~~##~~~~~~~##~~~##     ##~~##~##~~##~##~~##"
	@echo "$(RED)#####~~#####~~######~#####~~~~##~~~#####  ~####~~#####~~~####~~~~~~~###"
	@echo "$(RED)_______________________________________________________________________"
	@$(RM) $(OBJ)

fclean:
	@echo "$(RED)____________________________________________________________________"
	@echo "$(RED)#####~~#####~~##~~~~~#####~~######~#####  ~####~~##~~~~~##~~~~~~~###"
	@echo "$(RED)##~~##~##~~~~~##~~~~~##~~~~~~~##~~~##     ##~~##~##~~~~~##~~~~~~~###"
	@echo "$(RED)##~~##~####~~~##~~~~~####~~~~~##~~~####   ######~##~~~~~##~~~~~~~###"
	@echo "$(RED)##~~##~##~~~~~##~~~~~##~~~~~~~##~~~##     ##~~##~##~~~~~##"
	@echo "$(RED)#####~~#####~~######~#####~~~~##~~~#####  ##~~##~######~######~~~###"
	@echo "$(RED)____________________________________________________________________"
	@$(RM) $(NAME) $(OBJ)

re: fclean all	

.PHONY: all re clean fclean