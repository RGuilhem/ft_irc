#include "Server.hpp"
#include "Replies.hpp"
#include <iostream>
#include <algorithm>

Server::CommMap	Server::init_commands_map(void)
{
	CommMap comms;

	comms.insert(std::make_pair(std::string("PASS"), &Server::pass));
	comms.insert(std::make_pair(std::string("NICK"), &Server::nick));
	comms.insert(std::make_pair(std::string("USER"), &Server::user));
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
		client.appendSend(ERR_ALREADYREGISTERED(client.getNickname()));
		return ;
	}
	if (args.size() < 1)
	{
		client.appendSend(ERR_NEEDMOREPARAMS(client.getNickname(), comm));
		return ;
	}
	if (args[0] == password)
		client.setCorrectPass(true);
	else
	{
		client.setCorrectPass(false);
		client.appendSend(ERR_PASSWDMISMATCH(client.getNickname()));
	}
}

void	Server::nick(Client &client, Command &command)
{
	std::string	comm = command.getCommand();
	std::vector<std::string> args = command.getArgs();

	if (args.size() < 1)
	{
		client.appendSend(ERR_NONICKNAMEGIVEN(client.getNickname()));
		return ;
	}
	if (std::find(nicknames.begin(), nicknames.end(), args[0]) != nicknames.end())
	{
		client.appendSend(ERR_NICKNAMEINUSE(client.getNickname(), args[0]));
		return ;
	}
	if (args[0].find_first_of(":# ") != std::string::npos || args[0].size() == 0)
	{
		client.appendSend(ERR_ERRONEUSNICKNAME(client.getNickname(), args[0]));
		return ;
	}
	std::string	curr_nick = client.getNickname();
	client.setNickname(args[0]);
	nicknames.push_back(args[0]);
	if (curr_nick.size() != 0)
		nicknames.erase(std::find(nicknames.begin(), nicknames.end(), curr_nick));
	//TODO send message on nickname change
}

void	Server::user(Client &client, Command &command)
{
	std::string	comm = command.getCommand();
	std::vector<std::string> args = command.getArgs();
	
	if (client.getRegistered() == true)
	{
		client.appendSend(ERR_ALREADYREGISTERED(client.getNickname()));
		return ;
	}
	if (args.size() != 4 || args[0].size() == 0 || args[1] != "0" || args[2] != "*")
	{
		client.appendSend(ERR_NEEDMOREPARAMS(client.getNickname(), comm));
		return ;
	}
	client.setUsername("~" + args[0]);
	client.setRealname(args[3]);
	client.checkRegistration();
	if (client.getRegistered())
	{
		client.appendSend(RPL_WELCOME(client.getNickname(), client.getId()));
		client.appendSend(RPL_YOURHOST(client.getNickname()));
		client.appendSend(RPL_CREATED(client.getNickname(), "placeholder date"));
		client.appendSend(RPL_MYINFO(client.getNickname()));
		client.appendSend(RPL_ISUPPORT(client.getNickname()));
	}
}
