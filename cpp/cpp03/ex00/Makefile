NAME	= ClapTrap
SRC		= ClapTrap.cpp main.cpp
OBJ		= $(SRC:.cpp=.o)
DEPS	= $(OBJ:.o=.d)
FLAGS	= -Wall -Wextra -Werror -std=c++98 -MMD
CC		= c++
RM		= rm -rf

all: $(NAME)

%.o: %.cpp
	$(CC) $(FLAGS) -c $< -o $@

$(NAME): $(OBJ)
		$(CC) $(FLAGS) $(OBJ) -o $(NAME)
clean:
	$(RM) $(OBJ) $(DEPS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

-include $(DEPS)

.PHONY:	all clean fclean re