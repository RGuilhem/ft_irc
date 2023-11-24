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
	//TODO validate commmand
}
