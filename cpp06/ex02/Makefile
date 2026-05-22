SRC = Base.cpp C.cpp B.cpp A.cpp main.cpp 
OBJ = $(SRC:.cpp=.o)
NAME = Identify

all: $(NAME)

$(NAME): $(OBJ)
	c++ -Wall -Werror -Wextra -std=c++98 $(OBJ) -o $(NAME)

%.o: 	%.cpp A.hpp Base.hpp C.hpp B.hpp
	c++ -Wall -Werror -Wextra -std=c++98 -c $< -o $@

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re:	fclean all