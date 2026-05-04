SRC = main.cpp ScalarConverter.cpp
OBJ = $(SRC:.cpp=.o)
NAME = a.out

all: $(NAME)

$(NAME): $(OBJ)
	c++ -Wall -Werror -Wextra $(OBJ) -o $(NAME)

%.o:	%.cpp ScalarConverter.hpp
	c++ -Wall -Werror -Wextra -c $< -o $@

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re:	fclean all;