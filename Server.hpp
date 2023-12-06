/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: graux <marvin@42lausanne.ch>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 15:44:52 by graux             #+#    #+#             */
/*   Updated: 2023/12/06 13:01:55 by graux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
# define SERVER_HPP

# include "Client.hpp"
# include "Channel.hpp"
# include "Command.hpp"
# include <string>
# include <sys/types.h>
# include <sys/socket.h>
# include <netdb.h>
# include <poll.h>
# include <netinet/in.h>
# include <arpa/inet.h>
# include <map>
# include <vector>
# include <fstream>
# include <ctime>

# define BACKLOG 10
# define BUFF_SIZE 512
# define GREEN "\e[0;32m"
# define BLUE "\e[0;34m"
# define RESET_COL "\e[0m"

extern bool server_off;

class Server
{
	typedef void (Server::*Exec_func)(Client &, Command &);
	typedef std::map<std::string, Exec_func> CommMap;
	private:
	static CommMap	commands_map;
	static CommMap	init_commands_map(void);
	std::string		start_time;
	std::string		password;
	std::string		port;
	int				iport;
	int				sockfd;
	void			newConnection(std::vector<pollfd> &pollfds);
	void			recvClient(std::vector<pollfd> &pollfds, pollfd &pfd);
	void			sendClient(std::vector<pollfd> &pollfds, pollfd &pfd);
	void			parseMessage(Client &client);
	std::ofstream	logfile;

	std::map<int, Client>		clients;
	Client  &clientFromNick(std::string nick);
	void	broadcast(std::string msg, std::vector<std::string> const &targets);
	std::vector<std::string>	nicknames;
	std::vector<Channel>        channels;
	bool    channelExists(std::string name);
	Channel    &channelFromName(std::string name);
	void	logmsg(std::string msg);
	public:
	Server(void);
	~Server(void);
	Server(Server const &s);
	Server &operator=(Server const &s);

	Server(std::string port_str, std::string pass);
	void	lnch(void);
	void	run(void);
	std::string	getPort(void) const;

	//Server commands
	static bool	isCommand(std::string comm);
	void	pass(Client &client, Command &command);
	void	nick(Client &client, Command &command);
	void	user(Client &client, Command &command);
	void	cap(Client &client, Command &command);
	void	ping(Client &client, Command &command);
	void	quit(Client &client, Command &command);
	void	join(Client &client, Command &command);
	void	privmsg(Client &client, Command &command);
	void	part(Client &client, Command &command);
	void	kick(Client &client, Command &command);
	void	invite(Client &client, Command &command);
	void	mode(Client &client, Command &command);
	void	topic(Client &client, Command &command);
	void	who(Client &client, Command &command);
};

std::ostream &operator<<(std::ostream &o, const Server &s);

#endif
