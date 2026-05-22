SRC = main.cpp Serializer.cpp
OBJ = $(SRC:.cpp=.o)
NAME = Serializer

all: $(NAME)

$(NAME): $(OBJ)
	c++ -Wall -Werror -Wextra -std=c++98 $(OBJ) -o $(NAME)

%.o: 	%.cpp Data.hpp Serializer.hpp
	c++ -Wall -Werror -Wextra -std=c++98 -c $< -o $@

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re:	fclean all;