#include "Server.hpp"
#include "Replies.hpp"
#include "Botty.hpp"
#include <iostream>
#include <algorithm>
#include <set>

Server::CommMap	Server::init_commands_map(void)
{
	CommMap comms;

	comms.insert(std::make_pair(std::string("PASS"), &Server::pass));
	comms.insert(std::make_pair(std::string("NICK"), &Server::nick));
	comms.insert(std::make_pair(std::string("USER"), &Server::user));
	comms.insert(std::make_pair(std::string("CAP"), &Server::cap));
	comms.insert(std::make_pair(std::string("PING"), &Server::ping));
	comms.insert(std::make_pair(std::string("QUIT"), &Server::quit));
	comms.insert(std::make_pair(std::string("JOIN"), &Server::join));
	comms.insert(std::make_pair(std::string("PRIVMSG"), &Server::privmsg));
	comms.insert(std::make_pair(std::string("PART"), &Server::part));
	comms.insert(std::make_pair(std::string("KICK"), &Server::kick));
	comms.insert(std::make_pair(std::string("INVITE"), &Server::invite));
	comms.insert(std::make_pair(std::string("MODE"), &Server::mode));
	comms.insert(std::make_pair(std::string("TOPIC"), &Server::topic));
	comms.insert(std::make_pair(std::string("WHO"), &Server::who));
	return (comms);
}

bool	Server::isCommand(std::string comm)
{
	if (commands_map.find(comm) != commands_map.end())
		return (true);
	else
		return (false);
}

void	Server::pass(Client &client, Command &command)
{
	std::string	comm = command.getCommand();
	std::vector<std::string> args = command.getArgs();

	if (client.getRegistered() == true)
	{
		client.appendSend(ERR_ALREADYREGISTERED(client.getNickname()));
		return ;
	}
	if (args.size() < 1)
	{
		client.appendSend(ERR_NEEDMOREPARAMS(client.getNickname(), comm));
		return ;
	}
	if (args[0] == password)
		client.setCorrectPass(true);
	else
	{
		client.setCorrectPass(false);
		client.appendSend(ERR_PASSWDMISMATCH(client.getNickname()));
	}
}

void	Server::nick(Client &client, Command &command)
{
	std::string	comm = command.getCommand();
	std::vector<std::string> args = command.getArgs();

	if (args.size() < 1 || args[0].empty())
	{
		client.appendSend(ERR_NONICKNAMEGIVEN(client.getNickname()));
		return ;
	}
	if (std::find(nicknames.begin(), nicknames.end(), args[0]) != nicknames.end())
	{
		client.appendSend(ERR_NICKNAMEINUSE(client.getNickname(), args[0]));
		return ;
	}
	if (args[0].find_first_of(":# ,*?@!$.") != std::string::npos || args[0].size() == 0)
	{
		client.appendSend(ERR_ERRONEUSNICKNAME(client.getNickname(), args[0]));
		return ;
	}
	std::string	curr_nick = client.getNickname();
	client.setNickname(args[0]);
	nicknames.push_back(args[0]);
	if (curr_nick.size() != 0)
	{
		std::set<std::string>	to_broadcast;
		for (unsigned int i = 0; i < channels.size(); i++)
		{
			bool is_in = channels[i].isInChannel(client);
			channels[i].removeFromChannel(client);
			if (is_in)
			{
				std::vector<std::string> names_in_chan = channels[i].getUsersNicks();
				to_broadcast.insert(names_in_chan.begin(), names_in_chan.end());
			}
		}
		broadcast(":" + curr_nick + " NICK " + args[0], std::vector<std::string>(to_broadcast.begin(), to_broadcast.end()));
		nicknames.erase(std::find(nicknames.begin(), nicknames.end(), curr_nick));
	}
}

void	Server::user(Client &client, Command &command)
{
	std::string	comm = command.getCommand();
	std::vector<std::string> args = command.getArgs();

	if (client.getRegistered() == true)
	{
		client.appendSend(ERR_ALREADYREGISTERED(client.getNickname()));
		return ;
	}
	if (args.size() != 4 || args[0].size() == 0)
	{
		client.appendSend(ERR_NEEDMOREPARAMS(client.getNickname(), comm));
		return ;
	}
	client.setUsername("~" + args[0]);
	client.setRealname(args[3]);
	client.checkRegistration();
	if (client.getRegistered())
	{
		client.appendSend(RPL_WELCOME(client.getNickname(), client.getId()));
		client.appendSend(RPL_YOURHOST(client.getNickname()));
		client.appendSend(RPL_CREATED(client.getNickname(), start_time));
		client.appendSend(RPL_MYINFO(client.getNickname()));
		client.appendSend(RPL_ISUPPORT(client.getNickname()));

		client.appendSend(RPL_MOTDSTART(client.getNickname()));
		client.appendSend(RPL_MOTD(client.getNickname(), "Hello there!"));
		client.appendSend(RPL_ENDOFMOTD(client.getNickname()));
		client.appendSend(PRIVMSG(botty.getNickname(), client.getNickname(), botty.greet()));
	}
}

void	Server::cap(Client &client, Command &command)
{
	std::vector<std::string> args = command.getArgs();
	if (args.size() > 0 && args[0] != "END")
		client.appendSend(":localhost CAP * LS");
}

void	Server::ping(Client &client, Command &command)
{
	std::vector<std::string> args = command.getArgs();
	if (args.size() != 0)
		client.appendSend(":localhost PONG " + args[0]);
}

void	Server::quit(Client &client, Command &command)
{
	std::vector<std::string> args = command.getArgs();

	std::string reason = "";
	if (args.size() > 0)
		reason = args[0];
	std::set<std::string>	to_broadcast;
	for (unsigned int i = 0; i < channels.size(); i++)
	{
		bool is_in = channels[i].isInChannel(client);
		channels[i].removeFromChannel(client);
		if (is_in)
		{
			std::vector<std::string> names_in_chan = channels[i].getUsersNicks();
			to_broadcast.insert(names_in_chan.begin(), names_in_chan.end());
		}
	}
	broadcast(QUIT(client.getNickname(), reason), std::vector<std::string>(to_broadcast.begin(), to_broadcast.end()));
	client.appendSend(ERROR(reason));
}

void	Server::join(Client &client, Command &command)
{
	std::string	comm = command.getCommand();
	std::vector<std::string> args = command.getArgs();
	if (args.size() == 0 || args[0].length() == 0)
	{
		client.appendSend(ERR_NEEDMOREPARAMS(client.getNickname(), comm));
		return ;
	}
	std::string	name = args[0];
	if (name[0] != '#' || name.find_first_of(" \a,") != std::string::npos)
	{
		client.appendSend(ERR_BADCHANMASK(name));
		return ;
	}
	if (!channelExists(name)) //create new channel
	{
		Channel   newChannel(name, client);
		channels.push_back(newChannel);
	}
	else //try to connect to existing channel
	{
		try {
			Channel &chan = channelFromName(name);
			if (args.size() >= 2)
				chan.join(client, args[1]);
			else
				chan.join(client, "");
			broadcast(JOIN(client.getNickname(), name), chan.getUsersNicks());
			chan.greet(client);
		} catch (std::exception &e) {
			std::string response(e.what());
			if (!response.empty())
				client.appendSend(response);
		}
	}
}

void	Server::privmsg(Client &client, Command &command)
{
	(void) client;
	std::string	comm = command.getCommand();
	std::vector<std::string> args = command.getArgs();

	if (args.size() < 2)
	{
		client.appendSend(ERR_NEEDMOREPARAMS(client.getNickname(), comm));
		return ;
	}
	std::string target = args[0];
	std::string message = args[1];
	if (std::find(nicknames.begin(), nicknames.end(), target) != nicknames.end()) //msg to user
	{
		Client &c_target = clientFromNick(target);
		c_target.appendSend(PRIVMSG(client.getNickname(), target, message));
	}
	else if (!target.empty() && target[0] == '#') //msg to channel
	{
		if (channelExists(target))
		{
			Channel	&chan = channelFromName(target);
			if (chan.isInChannel(client))
			{
				std::vector<std::string> names = chan.getUsersNicks();
				names.erase(std::find(names.begin(), names.end(), client.getNickname()));
				broadcast(PRIVMSG(client.getNickname(), target, message), names);
			}
		}
	}
	else
		client.appendSend(ERR_NOSUCHNICK(client.getNickname(), target));
}

void	Server::part(Client &client, Command &command)
{
	std::string	comm = command.getCommand();
	std::vector<std::string> args = command.getArgs();

	if (args.size() == 0)
	{
		client.appendSend(ERR_NEEDMOREPARAMS(client.getNickname(), comm));
		return ;
	}
	if (!channelExists(args[0]))
	{
		client.appendSend(ERR_NOSUCHCHANNEL(client.getNickname(), args[0]));
		return ;
	}
	Channel	&chan = channelFromName(args[0]);
	std::vector<std::string> chan_nicks = chan.getUsersNicks();
	if (chan.isInChannel(client))
	{
		chan.removeFromChannel(client);
		if (args.size() < 2)
		{
			client.appendSend(PART(client.getNickname(), args[0], ""));
			broadcast(PART(client.getNickname(), args[0], ""), chan.getUsersNicks());
		}
		else
		{
			client.appendSend(PART(client.getNickname(), args[0], args[1]));
			broadcast(PART(client.getNickname(), args[0], args[1]), chan.getUsersNicks());
		}
	}
	else
		client.appendSend(ERR_NOTONCHANNEL(client.getNickname(), args[0]));
}

void	Server::kick(Client &client, Command &command)
{
	std::string	comm = command.getCommand();
	std::vector<std::string> args = command.getArgs();

	if (args.size() < 2)
	{
		client.appendSend(ERR_NEEDMOREPARAMS(client.getNickname(), comm));
		return ;
	}
	if (!channelExists(args[0]))
	{
		client.appendSend(ERR_NOSUCHCHANNEL(client.getNickname(), args[0]));
		return ;
	}
	Channel	&chan = channelFromName(args[0]);
	if (!chan.isOperator(client))
	{
		client.appendSend(ERR_CHANOPRIVSNEEDED(client.getNickname(), args[0]));
		return ;
	}
	std::vector<std::string> chan_nicks = chan.getUsersNicks();
	if (std::find(chan_nicks.begin(), chan_nicks.end(), args[1]) == chan_nicks.end())
	{
		client.appendSend(ERR_USERNOTINCHANNEL(client.getNickname(), args[1], args[0]));
		return ;
	}
	if (chan.isInChannel(client))
	{
		Client &to_remove = clientFromNick(args[1]);
		if (args.size() >= 3)
			broadcast(KICK(client.getNickname(), args[0], args[1], args[2]), chan.getUsersNicks());
		else
			broadcast(KICK(client.getNickname(), args[0], args[1], ""), chan.getUsersNicks());
		chan.removeFromChannel(to_remove);
	}
	else
		client.appendSend(ERR_NOTONCHANNEL(client.getNickname(), args[0]));

}
void	Server::invite(Client &client, Command &command)
{
	std::string	comm = command.getCommand();
	std::vector<std::string> args = command.getArgs();

	if (args.size() < 2)
	{
		client.appendSend(ERR_NEEDMOREPARAMS(client.getNickname(), comm));
		return ;
	}
	std::string	chan_name = args[1];
	std::string	invited_nick = args[0];
	if (!channelExists(chan_name))
	{
		client.appendSend(ERR_NOSUCHCHANNEL(client.getNickname(), chan_name));
		return ;
	}
	Channel	&chan = channelFromName(chan_name);
	if (!chan.isInChannel(client))
	{
		client.appendSend(ERR_NOTONCHANNEL(client.getNickname(), chan_name));
		return ;
	}
	std::vector<std::string> chan_nicks = chan.getUsersNicks();
	if (std::find(chan_nicks.begin(), chan_nicks.end(), chan_name) != chan_nicks.end())
	{
		client.appendSend(ERR_USERONCHANNEL(client.getNickname(), invited_nick, chan_name));
		return ;
	}
	if (!chan.isOperator(client) && chan.getInviteOnly())
	{
		client.appendSend(ERR_CHANOPRIVSNEEDED(client.getNickname(), chan_name));
		return ;
	}
	client.appendSend(RPL_INVITING(client.getNickname(), invited_nick, chan_name));
	Client	&invited = clientFromNick(invited_nick);
	chan.invite(invited);
	invited.appendSend(INVITE(client.getNickname(), invited_nick, chan_name));
}

void	Server::mode(Client &client, Command &command)
{
	std::string	comm = command.getCommand();
	std::vector<std::string> args = command.getArgs();

	if (args.size() < 1)
	{
		client.appendSend(ERR_NEEDMOREPARAMS(client.getNickname(), comm));
		return ;
	}
	std::string target = args[0];
	if (std::find(nicknames.begin(), nicknames.end(), target) != nicknames.end())
	{
		client.appendSend(RPL_UMODEIS(client.getNickname(), "+i"));
		return ;
	}
	if (!channelExists(target))
	{
		client.appendSend(ERR_NOSUCHCHANNEL(client.getNickname(), target));
		return ;
	}
	Channel	&chan = channelFromName(target);
	if (args.size() == 1) //show mode
		client.appendSend(RPL_CHANNELMODEIS(client.getNickname(), target, chan.modeString()));
	else if (chan.isOperator(client)) //set mode
	{
		chan.changeMode(args, client);
		client.appendSend(RPL_CHANNELMODEIS(client.getNickname(), target, chan.modeString()));
	}
	else
		client.appendSend(ERR_CHANOPRIVSNEEDED(client.getNickname(), target));
}

void	Server::topic(Client &client, Command &command)
{
	std::string	comm = command.getCommand();
	std::vector<std::string> args = command.getArgs();

	if (args.size() == 0)
	{
		client.appendSend(ERR_NEEDMOREPARAMS(client.getNickname(), comm));
		return ;
	}
	std::string target = args[0];
	if (!channelExists(target))
	{
		client.appendSend(ERR_NOSUCHCHANNEL(client.getNickname(), target));
		return ;
	}
	Channel	&chan = channelFromName(target);
	if (!chan.isInChannel(client))
	{
		client.appendSend(ERR_NOTONCHANNEL(client.getNickname(), target));
		return ;
	}
	if (args.size() > 1)
	{
		if (!chan.isOperator(client) && chan.getTopicOperator())
		{
			client.appendSend(ERR_CHANOPRIVSNEEDED(client.getNickname(), target));
			return ;
		}
		chan.setTopic(args[1]);
		std::string topic = chan.getTopic();
		std::string response;
		if (topic.empty())
			response = RPL_NOTOPIC(client.getNickname(), target);
		else
			response = RPL_TOPIC(client.getNickname(), target, topic);
		broadcast(response, chan.getUsersNicks());
	}
	else
	{
		std::string topic = chan.getTopic();
		if (topic.empty())
			client.appendSend(RPL_NOTOPIC(client.getNickname(), target));
		else
			client.appendSend(RPL_TOPIC(client.getNickname(), target, topic));
	}
}

void	Server::who(Client &client, Command &command)
{
	std::string	comm = command.getCommand();
	std::vector<std::string> args = command.getArgs();

	if (args.size() >= 1)
	{
		std::string target = args[0];
		if (channelExists(target))
		{
			Channel &chan = channelFromName(target);
			std::vector<std::string> nicks = chan.getUsersNicks();
			for (unsigned int i = 0; i < nicks.size(); i++)
			{
				Client &c = clientFromNick(nicks[i]);
				client.appendSend(RPL_WHOREPLY(c.getNickname(),
							target, c.getUsername(), c.getHostname(), c.getRealname()));
			}
		}
		client.appendSend(RPL_ENDOFWHO(client.getNickname(), target));
	}
}
