#include "Channel.hpp"
#include "Replies.hpp"
#include "Server.hpp"
#include <iostream>

Channel::Channel(std::string const &name, Client &creator)
{
	this->name = name;
	//TODO set default channel modes correctly
	invite_only = false;
	topic_operator = true;
	password = "";
	user_limit = 10;
	operators.push_back(creator);
	users.push_back(creator);
	creator.appendSend(JOIN(creator.getNickname(), name));
}

std::string Channel::getName(void) const
{
	return (name);
}

void Channel::join(Client &client, std::string pass)
{
	//TODO throw on invalid join
	if (std::find(users.begin(), users.end(), client) != users.end())
		throw std::invalid_argument("");
	if (pass != this->password)
		throw std::invalid_argument(ERR_BADCHANNELKEY(client.getNickname(), name));
	if (invite_only && std::find(invited.begin(), invited.end(), client) == invited.end())
		throw std::invalid_argument(ERR_INVITEONLYCHAN(client.getNickname(), name));
	if (users.size() == user_limit)
		throw std::invalid_argument(ERR_CHANNELISFULL(client.getNickname(), name));
	if (std::find(banned.begin(), banned.end(), client) != banned.end())
		throw std::invalid_argument(ERR_BANNEDFROMCHAN(client.getNickname(), name));
	//if everything is okay add client
	users.push_back(client);
}

std::vector<std::string> Channel::getUsersNicks(void) const
{
	std::vector<std::string>	resp;

	for (unsigned int i = 0; i < users.size(); i++)
		resp.push_back(users[i].getNickname());
	return (resp);
}
