/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppotier <ppotier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 10:44:06 by ppotier           #+#    #+#             */
/*   Updated: 2023/11/23 14:03:31 by ppotier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Channel.hpp"
#include <string>
#include <iostream>

Channel::Channel(std::string const &channelName) : name(channelName)
{
	topic.clear();
	channelpassword.clear();
	user_limit = -1;
	invite_only = false;
	topic_operator = true;
}

/*GETERS*/

std::string const& Channel::getname() const { return (this->name); }

std::string const& Channel::getTopic() const { return (this->topic); }

std::string const& Channel::getchannelpassword() const { return (this->channelpassword); }

int	Channel::getuserlimit() { return (this->user_limit); }

bool Channel::getinviteonly() { return (this->invite_only); }

bool Channel::gettopicoperator() { return (this->topic_operator); }

