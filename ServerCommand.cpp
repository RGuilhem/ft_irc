#include "Server.hpp"
#include "Replies.hpp"
#include <iostream>
#include <algorithm>

Server::CommMap	Server::init_commands_map(void)
{
	CommMap comms;

	comms.insert(std::make_pair(std::string("PASS"), &Server::pass));
	comms.insert(std::make_pair(std::string("NICK"), &Server::nick));
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

void	Server::nick(Client &client, Command &command)
{
	std::string	comm = command.getCommand();
	std::vector<std::string> args = command.getArgs();

	if (args.size() < 1)
	{
		client.appendSend(ERR_NONICKNAMEGIVEN(client.getId()));
		return ;
	}
	if (std::find(nicknames.begin(), nicknames.end(), args[0]) != nicknames.end())
	{
		client.appendSend(ERR_NICKNAMEINUSE(client.getId(), args[0]));
		return ;
	}
	if (args[0].find_first_of(":# ") != std::string::npos || args[0].size() == 0)
	{
		client.appendSend(ERR_ERRONEUSNICKNAME(client.getId(), args[0]));
		return ;
	}
	std::string	curr_nick = client.getNickname();
	client.setNickname(args[0]);
	nicknames.push_back(args[0]);
	if (curr_nick.size() != 0)
		nicknames.erase(std::find(nicknames.begin(), nicknames.end(), curr_nick));
}
