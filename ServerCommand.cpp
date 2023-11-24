#include "Server.hpp"
#include "Replies.hpp"
#include <iostream>

Server::CommMap	Server::init_commands_map(void)
{
	CommMap comms;

	comms.insert(std::make_pair(std::string("PASS"), &Server::pass));
	return (comms);
}

bool	Server::isCommand(std::string comm)
{
	if (commands_map.find(comm) != commands_map.end())
		return (true);
	else
		return (false);
}

void	Server::pass(Client &client, Command &command)
{
	std::string	comm = command.getCommand();
	std::vector<std::string> args = command.getArgs();
	if (client.getRegistered() == true)
	{
		client.appendSend(ERR_ALREADYREGISTERED(client.getId()));
		return ;
	}
	if (args.size() < 1)
	{
		client.appendSend(ERR_NEEDMOREPARAMS(client.getId(), comm));
		return ;
	}
	if (args[0] == password)
		client.setCorrectPass(true);
	else
	{
		client.setCorrectPass(false);
		client.appendSend(ERR_PASSWDMISMATCH(client.getId()));
	}
}
