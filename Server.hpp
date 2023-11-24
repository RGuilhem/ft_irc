/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: graux <marvin@42lausanne.ch>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 15:44:52 by graux             #+#    #+#             */
/*   Updated: 2023/11/24 18:40:36 by graux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
# define SERVER_HPP

# include "Client.hpp"
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

# define BACKLOG 10
# define BUFF_SIZE 512

extern bool server_off;

class Server
{
	typedef void (Server::*Exec_func)(Client &, Command &);
	typedef std::map<std::string, Exec_func> CommMap;
	private:
		static CommMap	commands_map;
		static CommMap	init_commands_map(void);
		std::string		password;
		std::string		port;
		int				iport;
		int				sockfd;
		void			newConnection(std::vector<pollfd> &pollfds);
		void			recvClient(std::vector<pollfd> &pollfds, pollfd &pfd);
		void			sendClient(std::vector<pollfd> &pollfds, pollfd &pfd);
		void			parseMessage(Client &client);

		std::map<int, Client>		clients;
		std::vector<std::string>	nicknames;
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
};

std::ostream &operator<<(std::ostream &o, const Server &s);

#endif
