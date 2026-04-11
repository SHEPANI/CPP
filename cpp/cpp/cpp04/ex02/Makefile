NAME	= Animals
SRC		= main.cpp Animal.cpp Cat.cpp Dog.cpp WrongAnimal.cpp WrongCat.cpp Brain.cpp
OBJ		= $(SRC:.cpp=.o)
DEPS	= $(OBJ:.o=.d)
FLAGS	= -Wall -Wextra -Werror -std=c++98 -MMD
CXX		= c++
RM		= rm -rf

all: $(NAME)

%.o: %.cpp
		$(CXX) $(FLAGS) -c $< -o $@

$(NAME) : $(OBJ)
		$(CXX) $(FLAGS) $(OBJ) -o $(NAME)

clean:
		$(RM) $(OBJ) $(DEPS)

-include $(DEPS)

fclean: clean
		$(RM) $(NAME)

re : fclean all

.PHONY: clean
