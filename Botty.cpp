/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Botty.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: graux <marvin@42lausanne.ch>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 19:02:06 by graux             #+#    #+#             */
/*   Updated: 2023/12/06 21:08:29 by graux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Botty.hpp"
#include "Replies.hpp"
#include <sstream>
#include <cstdlib>
#include <ctime>

Botty::CommMap Botty::commands_map = Botty::init_commands_map();

Botty::CommMap	Botty::init_commands_map(void)
{
	CommMap	comms;

	comms.insert(std::make_pair(std::string("/help"), &Botty::help));
	comms.insert(std::make_pair(std::string("/coinflip"), &Botty::coinflip));
	return (comms);
}

bool	Botty::isCommand(std::string comm)
{
	if (commands_map.find(comm) != commands_map.end())
		return (true);
	else
		return (false);
}

Botty::Botty(void)
{
	std::srand(std::time(0));
}

Botty::~Botty(void)
{
}

std::string	Botty::greet(void) const
{
	return ("Hello I'm botty you can send me a /help to see what I can do!");
}

std::string	Botty::getNickname(void) const
{
	return ("botty");
}

void	Botty::sendMsg(Client &client, std::string message)
{
	client.appendSend(PRIVMSG(getNickname(), client.getNickname(), message));
}


void	Botty::handleMsg(Client &client, std::string message)
{
	std::stringstream	i_stream(message);
	std::string			command;
	std::string			token;
	std::vector<std::string>	args;

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
	if (isCommand(command))
	{
		Exec_func	func = commands_map[command];
		(this->*func)(client, command, args);
	}
	else
	{
		sendMsg(client, "Unknown command");
		help(client, command, args);
	}
}

void	Botty::help(Client &client, std::string command, std::vector<std::string> args)
{
	(void) command;
	(void) args;
	sendMsg(client, "usage: <command> [args...]");
	sendMsg(client, "Available commands:");
	sendMsg(client, "	/help -> list available commands, or display help about specific command");
	sendMsg(client, "	/coinflip -> filp a coin");
}

void	Botty::coinflip(Client &client, std::string command, std::vector<std::string> args)
{
	(void) command;
	(void) args;
	if (std::rand() % 2)
		sendMsg(client, "heads");
	else
		sendMsg(client, "tails");
}
