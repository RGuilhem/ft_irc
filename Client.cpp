/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: graux <marvin@42lausanne.ch>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 13:50:39 by graux             #+#    #+#             */
/*   Updated: 2023/11/23 15:09:45 by graux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Client.hpp"

Client::Client(int i) : fd(i)
{
	(void) fd;
}

void	Client::appendRead(std::string newData)
{
	read_buff += newData;
}

void	Client::resetReadBuff(void)
{
	read_buff.clear();
}

std::string Client::getReadBuff(void) const
{
  return (read_buff);
}

std::string Client::getSendBuff(void) const
{
  return (send_buff);
}
