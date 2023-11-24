#include "Server.hpp"

Server::CommMap	Server::init_commands_map(void)
{
	CommMap comms;

	comms.insert(std::make_pair(std::string("PASS"), &Server::pass));
	return (comms);
}

void	Server::pass(Client &client, Command &command)
{
	(void) client;
	(void) command;
}
