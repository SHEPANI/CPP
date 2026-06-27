NAME = EasyFind
SRCS = main.cpp easyfind.hpp
FLAGS = -Wall -Wextra -Werror -std=c++98 -MMD
OBJS = $(SRCS:.cpp=.o)
DEPS = $(OBJS:.o=.d)
CXX = c++
RM = rm -rf

all: $(NAME)

%.o: %.cpp
	$(CXX) $(FLAGS) -c $< -o $@

$(NAME): $(OBJS)
	$(CXX) $(FLAGS) $(OBJS) -o $(NAME)


clean:
	$(RM) $(OBJS) $(DEPS)

fclean: clean
	$(RM) $(NAME)

re : fclean all

.PHONY: all clean fclean re