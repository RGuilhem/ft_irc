#ifndef COMMAND_HPP
# define COMMAND_HPP

# include "Server.hpp"
# include <string>
# include <vector>

class Command
{
	private:
		std::string					source;
		std::string					command;
		std::vector<std::string>	args;
		Command(void);
	public:
		~Command(void);
		Command(std::string input); //clients can't send source so not in here
};

#endif
