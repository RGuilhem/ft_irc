/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: graux <marvin@42lausanne.ch>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 13:50:39 by graux             #+#    #+#             */
/*   Updated: 2023/11/24 21:08:49 by graux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Client.hpp"
#include <iostream>

Client::Client(int i) : fd(i)
{
	(void) fd;
	is_registered = false;
    hostname = "127.0.0.1";
}

Client::~Client(void)
{
	//TODO deregister nickname from server nicknames
}

void	Client::appendRead(std::string newData)
{
	read_buff += newData;
}

void	Client::appendSend(std::string newData)
{
	send_buff += newData;
	send_buff += "\r\n";
}

void	Client::resetReadBuff(void)
{
	read_buff.clear();
}

void	Client::clearEndReadBuff(void)
{
	read_buff.erase(read_buff.size() - 2, 2);
}

void	Client::clearSentSendBuff(int sent)
{
	if (sent != 0 && static_cast<unsigned int>(sent) == send_buff.size())
		send_buff.clear();
	else
		send_buff.erase(0, sent);
}

void	Client::checkRegistration(void)
{
	if (correct_pass && !nickname.empty() && !username.empty())
		is_registered = true;
}

std::string Client::getReadBuff(void) const
{
  return (read_buff);
}

std::string Client::getSendBuff(void) const
{
  return (send_buff);
}

std::string	Client::getId(void) const
{
	return (nickname + "!" + username + "@" + hostname);
}

bool	Client::getCorrectPass(void) const
{
	return (correct_pass);
}

void	Client::setCorrectPass(bool val)
{
	correct_pass = val;
}

bool	Client::getRegistered(void) const
{
	return (is_registered);
}

void	Client::setRegistered(bool val)
{
	is_registered = val;
}

std::string	Client::getNickname(void) const
{
	return (nickname);
}

void	Client::setNickname(std::string const &val)
{
	nickname = val;
}

std::string	Client::getUsername(void) const
{
	return (username);
}

void	Client::setUsername(std::string const &val)
{
	username = val;
}

std::string	Client::getRealname(void) const
{
	return (realname);
}

void	Client::setRealname(std::string const &val)
{
	realname = val;
}
