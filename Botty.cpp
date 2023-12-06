/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Botty.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: graux <marvin@42lausanne.ch>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 19:02:06 by graux             #+#    #+#             */
/*   Updated: 2023/12/06 20:26:34 by graux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Botty.hpp"
#include "Replies.hpp"
#include <sstream>

Botty::CommMap Botty::commands_map = Botty::init_commands_map();

Botty::CommMap	Botty::init_commands_map(void)
{
	CommMap	comms;

	comms.insert(std::make_pair(std::string("/help"), &Botty::help));
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
		sendMsg(client, "Unknown command");
}

void	Botty::help(Client &client, std::string command, std::vector<std::string> args)
{
	sendMsg(client, "usage: <command> [args...]");
	(void) command;
	(void) args;
}
