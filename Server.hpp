/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: graux <marvin@42lausanne.ch>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 15:44:52 by graux             #+#    #+#             */
/*   Updated: 2023/11/19 14:14:41 by graux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
# define SERVER_HPP

# include "Client.hpp"
# include <string>
# include <sys/types.h>
# include <sys/socket.h>
# include <netdb.h>
# include <poll.h>
# include <netinet/in.h>
# include <arpa/inet.h>
# include <map>

# define BACKLOG 10

extern bool server_off;

class Server
{
	private:
		std::string		password;
		std::string		port;
		std::map<int, Client> clients;
		int				iport;
		int				sockfd;
		void			newConnection(std::vector<pollfd> &pollfds);
		void			recvClient(std::vector<pollfd> &pollfds, pollfd &pfd);
		void			sendClient(std::vector<pollfd> &pollfds, pollfd &pfd);
	public:
		Server(void);
		~Server(void);
		Server(Server const &s);
		Server &operator=(Server const &s);

		Server(std::string port_str, std::string pass);
		void	lnch(void);
		void	run(void);
		std::string	getPort(void) const;
};

std::ostream &operator<<(std::ostream &o, const Server &s);

#endif
