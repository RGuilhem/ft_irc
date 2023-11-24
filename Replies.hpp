#ifndef REPLIES_HPP
# define REPLIES_HPP

//PASS
# define ERR_NEEDMOREPARAMS(client, command) (":localhost " + client + " " + command + " :Not enough parameters")
# define ERR_ALREADYREGISTERED(client) (":localhost " + client + " :You may not register")
# define ERR_PASSWDMISMATCH(client) (":localhost " + client + " :Password incorrect")
//NICK
# define ERR_NONICKNAMEGIVEN(client) (":localhost " + client + " :No nickname given")
# define ERR_ERRONEUSNICKNAME(client, nick) (":localhost " + client + " " + nick + " :Erroneus nickname")
# define ERR_NICKNAMEINUSE(client, nick) (":localhost " + client + " " + nick + " :Nickname is already in use")
//USER
# define RPL_WELCOME(client, id) (":localhost " + client + " :Welcome to ircserv, " + id)
# define RPL_YOURHOST(client) (":localhost " + client + " :Your host is ircserv, running version 0.1")
# define RPL_CREATED(client, date) (":localhost " + client + " :This server was created " + date)
# define RPL_MYINFO(client) (":localhost " + client + " ircserv v0.1 <user modes> <channel modes>")
# define RPL_ISUPPORT(client) (":localhost " + client + " :are supproted by this server")
//MOTD
# define RPL_MOTDSTART(client) (":localhost " + client + " :- ircserv Message of the day -")
# define RPL_MOTD(client, line) (":localhost " + client + " :" + line)
# define RPL_ENDOFMOTD(client) (":localhost " + client + " :End of /MOTD command")

#endif
