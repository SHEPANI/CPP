SRC = Base.cpp C.cpp B.cpp A.cpp main.cpp 
OBJ = $(SRC:.cpp=.o)
NAME = a.out

all: $(NAME)

$(NAME): $(OBJ)
	c++ -Wall -Werror -Wextra -std=c++98 $(OBJ) -o $(NAME)

%.o: 	%.cpp ScalarConverter.hpp
	c++ -Wall -Werror -Wextra -std=c++98 -c $< -o $@

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re:	fclean all;