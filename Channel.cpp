/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppotier <ppotier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 10:44:06 by ppotier           #+#    #+#             */
/*   Updated: 2023/11/23 10:53:55 by ppotier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Channel.hpp"

Channel::Channel(std::string const &channelName) : _name(channelName)
{
	_topic.clear();
	_channelPassword.clear();
}

Channel::~Channel(void) {}

/*GETERS*/

std::string& Channel::getname()
{
	return (this->_name);
}

std::string& Channel::topic()
{
	return (this->_topic);
}

std::string& Channel::channelpassword()
{
	return (this->_channelPassword);
}