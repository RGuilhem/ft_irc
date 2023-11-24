#include "Command.hpp"
#include "Server.hpp"
#include <sstream>

Command::~Command(void)
{
}

Command::Command(std::string input)
{
	std::stringstream	i_stream(input);
	std::string			token;

	i_stream >> command;
	while (i_stream >> token)
		args.push_back(token);
	if (!Server::isCommand(command))
		throw std::invalid_argument("Invalid command Exception");
}

std::string	Command::getCommand(void) const
{
	return (command);
}

std::vector<std::string>	Command::getArgs(void) const
{
	return (args);
}
