/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: graux <marvin@42lausanne.ch>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 15:44:52 by graux             #+#    #+#             */
/*   Updated: 2023/11/19 10:07:19 by graux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
# define SERVER_HPP

# include <string>

class Server
{
	private:
		std::string	password;
		int			port;
	public:
		Server(void);
		~Server(void);
		Server(Server const &s);
		Server &operator=(Server const &s);

		Server(std::string port_str, std::string pass);
};

#endif
