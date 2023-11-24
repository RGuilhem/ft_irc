#include "Server.hpp"
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
	(void) client;
	std::string	comm = command.getCommand();
	std::vector<std::string> args = command.getArgs();
	std::cout << "executing pass command '" << comm << "'" << std::endl;
	for (unsigned int i = 0; i < args.size(); i++)
	{
		std::cout << "'" << args[i] << "'" << std::endl;
	}
}
