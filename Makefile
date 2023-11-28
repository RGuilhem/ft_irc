CC = c++
FLAGS = -Wall -Wextra -Werror -g3 -std=c++98
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
	@$(MAKE) info

re: fclean all

clean:
	${RM} ${OBJ} $(DEPENDS)

fclean: clean
	${RM} ${NAME}

info:
	@echo -n "hostname: "
	@uname -n
	@echo -n "ip: "
	@hostname -I

.PHONY: all re clean fclean info
