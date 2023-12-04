#ifndef REPLIES_HPP
# define REPLIES_HPP

//PASS
# define ERR_NEEDMOREPARAMS(client, command) (":localhost 461 " + client + " " + command + " :Not enough parameters")
# define ERR_ALREADYREGISTERED(client) (":localhost 462 " + client + " :You may not register")
# define ERR_PASSWDMISMATCH(client) (":localhost 464 " + client + " :Password incorrect")
//NICK
# define ERR_NONICKNAMEGIVEN(client) (":localhost 431 " + client + " :No nickname given")
# define ERR_ERRONEUSNICKNAME(client, nick) (":localhost 432 " + client + " " + nick + " :Erroneus nickname")
# define ERR_NICKNAMEINUSE(client, nick) (":localhost 433 " + client + " " + nick + " :Nickname is already in use")
//USER
# define RPL_WELCOME(client, id) (":localhost 001 " + client + " :Welcome to ircserv, " + id)
# define RPL_YOURHOST(client) (":localhost 002 " + client + " :Your host is ircserv, running version 0.1")
# define RPL_CREATED(client, date) (":localhost 003 " + client + " :This server was created " + date)
# define RPL_MYINFO(client) (":localhost 004 " + client + " ircserv v0.1 <user modes> <channel modes>")
# define RPL_ISUPPORT(client) (":localhost 005 " + client + " :are supproted by this server")
//MOTD
# define RPL_MOTDSTART(client) (":localhost 375 " + client + " :- ircserv Message of the day -")
# define RPL_MOTD(client, line) (":localhost 372 " + client + " :" + line)
# define RPL_ENDOFMOTD(client) (":localhost 376 " + client + " :End of /MOTD command")

# define ERROR(reason) (":localhost ERROR :" + reason)

//JOIN
# define JOIN(source, channel) (":" + source + " JOIN " + channel)
# define ERR_BADCHANMASK(chan_name) (":localhost 476 " + chan_name + " :Bad channel mask")

#endif
