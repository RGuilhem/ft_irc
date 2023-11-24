#ifndef REPLIES_HPP
# define REPLIES_HPP

//PASS
# define ERR_NEEDMOREPARAMS(client, command) (client + " " + command + " :Not enough parameters")
# define ERR_ALREADYREGISTERED(client) (client + " :You may not register")
# define ERR_PASSWDMISMATCH(client) (client + " :Password incorrect")
//NICK
# define ERR_NONICKNAMEGIVEN(client) (client + " :No nickname given")
# define ERR_ERRONEUSNICKNAME(client, nick) (client + " " + nick + " :Erroneus nickname")
# define ERR_NICKNAMEINUSE(client, nick) (client + " " + nick + " :Nickname is already in use")

#endif
