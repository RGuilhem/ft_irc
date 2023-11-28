CC = c++
FLAGS = -Wall -Wextra -Werror -g3 -std=c++98
RM = rm -rf

SRC = main.cpp			\
	  Server.cpp		\
	  Channel.cpp		\
	  Command.cpp		\
	  ServerCommand.cpp	\
	  Client.cpp
#SRC_DIR = $(addprefix src/, $(SRC))
OBJ = ${SRC:.cpp=.o}

NAME = ircserv

#INCLUDES = -Iinclude/

%.o: %.cpp
	${CC} ${FLAGS} -c $< -o $@

all: ${NAME}

$(NAME): $(OBJ)
	$(CC) ${FLAGS} $(OBJ) -o $(NAME)
	@make info

re: fclean all

clean:
	${RM} ${OBJ}

fclean: clean
	${RM} ${NAME}

info:
	@echo -n "hostname: "
	@uname -n
	@echo -n "ip: "
	@hostname -I

.PHONY: all re clean fclean info
