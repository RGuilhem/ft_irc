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
	{
		if (token[0] == ':')
			break ;
		args.push_back(token);
	}
	if (token[0] == ':')
	{
		std::string tmp;
		std::getline(i_stream, tmp);
		args.push_back(token.erase(0, 1));
		args.back() += tmp;
	}
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
