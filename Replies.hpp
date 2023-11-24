#ifndef REPLIES_HPP
# define REPLIES_HPP

# define ERR_NEEDMOREPARAMS(client, command) (client + " " + command + " :Not enough parameters")
# define ERR_ALREADYREGISTERED(client) (client + " :You may not register")
# define ERR_PASSWDMISMATCH(client) (client + " :Password incorrect")

#endif
