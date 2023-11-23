/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppotier <ppotier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 10:32:41 by ppotier           #+#    #+#             */
/*   Updated: 2023/11/23 10:55:33 by ppotier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHANNEL_HPP
# define CHANNEL_HPP
#include <string>

class Channel
{
private:
	std::string _name;
	std::string _topic;
	std::string	_channelPassword;
public:
	Channel(std::string const &channelName);
	~Channel(void);
	std::string& getname();
	std::string& topic();
	std::string& channelpassword();
};

/*GETERS*/

#endif