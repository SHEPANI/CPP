NAME	= Bureaucrat
SRC		= Bureaucrat.cpp main.cpp AForm.cpp ShrubberyCreationForm.cpp RobotomyRequestForm.cpp PresidentialPardonForm.cpp
FLAGS	= -Wall -Wextra -Werror -std=c++98 -MMD
OBJ		= $(SRC:.cpp=.o)
DEPS	= $(OBJ:.o=.d)
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

	
