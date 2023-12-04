CC = c++
#TODO try to add -Weffc++
FLAGS = -Wall -Wextra -Werror -fsanitize=address -g -std=c++98
RM = rm -rf

SRC = main.cpp			\
	  Server.cpp		\
	  Channel.cpp		\
	  Command.cpp		\
	  ServerCommand.cpp	\
	  Client.cpp
OBJ = ${SRC:.cpp=.o}
DEPENDS = ${SRC:.cpp=.d}

NAME = ircserv

all: ${NAME}

-include ($(DEPENDS))

%.o: %.cpp Makefile
	${CC} ${FLAGS} -MMD -MP -c $< -o $@


$(NAME): $(OBJ)
	$(CC) ${FLAGS} $(OBJ) -o $(NAME)
	@echo "hostname: "
	@uname -n

re: fclean all

clean:
	${RM} ${OBJ} $(DEPENDS)

fclean: clean
	${RM} ${NAME}

.PHONY: all re clean fclean info
