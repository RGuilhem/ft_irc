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
# define QUIT(source, reason) (":" + source + " QUIT :Quit: " + reason)

//JOIN
# define JOIN(source, channel) (":" + source + " JOIN " + channel)
# define ERR_BADCHANMASK(channel) (":localhost 476 " + channel + " :Bad channel mask")
# define ERR_BADCHANNELKEY(client, channel) (":localhost 475 " + client + " " + channel + " :Cannot join channel (+k)")
# define ERR_INVITEONLYCHAN(client, channel) (":localhost 473 " + client + " " + channel + " :Cannot join channel (+i)")
# define ERR_CHANNELISFULL(client, channel) (":localhost 471 " + client + " " + channel + " :Cannot join channel (+l)")
# define ERR_BANNEDFROMCHAN(client, channel) (":localhost 474 " + client + " " + channel + " :Cannot join channel (+b)")
# define RPL_TOPIC(client, channel, topic) (":localhost 332 " + client + " " + channel + " :" + topic)
# define RPL_NAMREPLY(client, channel, name) (":localhost 353 " + client + " = " + channel + " :" + name)
# define RPL_ENDOFNAMES(client, channel) (":localhost 366 " + client + " " + channel + " :End of /Nameslist")

//PART
# define ERR_NOSUCHCHANNEL(client, channel) (":localhost 403 " + client + " " + channel + " :No such channel")
# define ERR_NOTONCHANNEL(client, channel) (":localhost 442 " + client + " " + channel + " :Not on channel")
# define PART(source, channel, reason) (":" + source + " PART " + channel + " :" + reason)

//KICK
# define ERR_CHANOPRIVSNEEDED(client, channel) (":localhost 482 " + client + " " + channel + " :You are not channel operator")
# define ERR_USERNOTINCHANNEL(client, nick, channel) (":localhost 441 " + client + " " + nick + " " + channel + " :They are not on that channel")
# define KICK(source, channel, nick, reason) (":" + source + " KICK " + channel + " " + nick + " :" + reason)

#endif
