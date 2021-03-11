##
## EPITECH PROJECT, 2019
## project name
## File description:
## Makefile
##

CXX = clang++

NAME = engine

SRC_MAIN = src/main.cpp

SRC_OTHERS =

SRC_TEST =

SRC = $(SRC_OTHERS)

OBJ = $(SRC:.cpp=.o) $(SRC_MAIN:.cpp=.o)

CPPFLAGS =

CXXFLAGS = -Wall -Wextra

LDFLAGS =

LDLIBS =

all: $(NAME)

$(NAME): $(OBJ)
	$(CXX) -o $(NAME) $(OBJ) $(LDFLAGS) $(LDLIBS)

debug: CXXFLAGS += -g3 -D DEBUG
debug: fclean $(NAME)

clean:
	$(RM) $(NAME)

fclean: clean
	$(RM) $(OBJ)

re: fclean all

.PHONY: all clean fclean re debug
