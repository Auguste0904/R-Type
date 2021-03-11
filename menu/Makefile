##
## EPITECH PROJECT, 2019
## Makefile
## File description:
## Makefile
##

NAME	=	menu

CC		=	g++

SRC		=	src/Exception/Exception.cpp				\
			src/Menus/AMenu.cpp						\
			src/Menus/MainMenu.cpp					\
			src/Menus/SettingsMenu.cpp				\
			src/Menus/HtpMenu.cpp					\
			src/Menus/RoomManagement.cpp			\
			src/Menus/CreateRoom.cpp				\
			src/Menus/JoinRoom.cpp					\
			main.cpp								\

OBJ		=	$(SRC:.cpp=.o)

CFLAGS		+=	-I./includes	\
				-I./includes/Menus	\
				-I./includes/Exceptions

LDFLAGS 	=	-Wall -Wextra -W -g3

LFLAGS		=	-lsfml-window -lsfml-system -lsfml-audio -lsfml-graphics

all:	$(NAME)

%.o:	%.cpp
			@$(CC) $(CFLAGS) $(LDFLAGS) $(LFLAGS) -c -o $@ $<
			@echo "\033[0;32m[OK]    \033[1;32m" $< "\033[0m"

$(NAME):	$(OBJ)
			@echo "\033[0;34m[OK]     \033[1;34mObj's files successfully compiled!\033[0m"
			@$(CC) -o $(NAME) $(OBJ) $(CFLAGS) $(LFLAGS)
			@echo "\033[0;34m[OK]    \033[1;34m" $(NAME) "successfully created!\033[0m\n"

run:	re
			@./$(NAME)

debug:	fclean $(OBJ)
			@echo "\033[0;34m[OK]     \033[1;34mObj's files successfully compiled!\033[0m"
			@$(CC) -o $(NAME) $(OBJ) $(CFLAGS) $(LFLAGS)
			@echo "\033[0;34m[OK]    \033[1;34m" $(NAME) "successfully created!\033[1;33m\n"
			@valgrind ./$(NAME)
clean:
			@rm -f $(OBJ)
			@rm -f $(TEST)

fclean:	clean
			@rm -f $(shell find . -name "*~")
			@rm -f $(shell find . -name "a.out")
			@rm -f $(shell find . -name "vgcore.*")
			@rm -f $(shell find . -name "\#*#")
			@rm -f $(shell find . -name "*.gc*")
			@rm -f $(shell find . -name ".safe")
			@rm -f $(NAME)
			@echo "\033[0;33m[OK]     \033[1;33msuccessfully cleaned!\033[0m"

re:	fclean
	@make -j

.PHONY:	all	clean	fclean	re	debug	run
