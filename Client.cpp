/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: graux <marvin@42lausanne.ch>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 13:50:39 by graux             #+#    #+#             */
/*   Updated: 2023/11/23 16:41:47 by graux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Client.hpp"
#include <iostream>

Client::Client(int i) : fd(i)
{
	(void) fd;
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
	if (static_cast<unsigned int>(sent) == send_buff.size())
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
