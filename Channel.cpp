#include "Channel.hpp"
#include "Replies.hpp"
#include "Server.hpp"

Channel::Channel(std::string const &name, Client &creator)
{
	this->name = name;
	//TODO set default channel modes correctly
	invite_only = false;
	topic_operator = true;
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
	(void) pass;
	users.push_back(client);
}

std::vector<std::string> Channel::getUsersNicks(void) const
{
	std::vector<std::string>	resp;

	for (unsigned int i = 0; i < users.size(); i++)
		resp.push_back(users[i].getNickname());
	return (resp);
}
