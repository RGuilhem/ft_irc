/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: graux <marvin@42lausanne.ch>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 13:50:39 by graux             #+#    #+#             */
/*   Updated: 2023/11/24 16:41:20 by graux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Client.hpp"
#include <iostream>

Client::Client(int i) : fd(i)
{
	(void) fd;
	is_registered = false;
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
	read_buff.pop_back();
	read_buff.pop_back();
}

void	Client::clearSentSendBuff(int sent)
{
	if (sent != 0 && static_cast<unsigned int>(sent) == send_buff.size())
		send_buff.clear();
	else
		send_buff.erase(0, sent);
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
