/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: graux <marvin@42lausanne.ch>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 15:44:52 by graux             #+#    #+#             */
/*   Updated: 2023/11/19 12:06:49 by graux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
# define SERVER_HPP

# include <string>
# include <sys/types.h>
# include <sys/socket.h>
# include <netdb.h>

# define BACKLOG 10

class Server
{
	private:
		std::string		password;
		std::string		port;
		int				iport;
		int				sockfd;
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
