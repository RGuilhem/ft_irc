#include "Server.hpp"
#include "Replies.hpp"
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

	if (args.size() < 1)
	{
		client.appendSend(ERR_NONICKNAMEGIVEN(client.getNickname()));
		return ;
	}
	if (std::find(nicknames.begin(), nicknames.end(), args[0]) != nicknames.end())
	{
		client.appendSend(ERR_NICKNAMEINUSE(client.getNickname(), args[0]));
		return ;
	}
	if (args[0].find_first_of(":# ") != std::string::npos || args[0].size() == 0) //TODO , invalid
	{
		client.appendSend(ERR_ERRONEUSNICKNAME(client.getNickname(), args[0]));
		return ;
	}
	std::string	curr_nick = client.getNickname();
	client.setNickname(args[0]);
	nicknames.push_back(args[0]);
	if (curr_nick.size() != 0) // TODO broadcast nick change to other users
	{
		nicknames.erase(std::find(nicknames.begin(), nicknames.end(), curr_nick));
		client.appendSend(":" + curr_nick + " NICK " + args[0]);
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
		client.appendSend(RPL_CREATED(client.getNickname(), "placeholder date"));
		client.appendSend(RPL_MYINFO(client.getNickname()));
		client.appendSend(RPL_ISUPPORT(client.getNickname()));

		client.appendSend(RPL_MOTDSTART(client.getNickname()));
		client.appendSend(RPL_MOTD(client.getNickname(), "Hello there!"));
		client.appendSend(RPL_ENDOFMOTD(client.getNickname()));
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
		client.appendSend(":localhost PONG " + args[0]); //TODO handle token starting with :
}

void	Server::quit(Client &client, Command &command)
{
	//TODO broadcast quit to channels client is quiting
	//TODO exit channels
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
	if (name[0] != '#')
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
			Channel &chan = channelFromName(name); //TODO add pw
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
	//TODO implement privmsg
	(void) client;
	std::string	comm = command.getCommand();
	std::vector<std::string> args = command.getArgs();
}

void	Server::part(Client &client, Command &command)
{
	std::string	comm = command.getCommand();
	std::vector<std::string> args = command.getArgs();

	if (args.size() == 0)
	{
		client.appendSend(ERR_NEEDMOREPARAMS(client.getNickname(), comm));
		return ;
	} //TODO add error checking PART
	if (!channelExists(args[0]))
	{
		//TODO nosuchchan
		return ;
	}
	Channel	&chan = channelFromName(args[0]);
	std::vector<std::string> chan_nicks = chan.getUsersNicks();
	if (std::find(chan_nicks.begin(), chan_nicks.end(), client.getNickname()) != chan_nicks.end())
	{
	}
	else
	{
		//TODO notonchan
	}
}
