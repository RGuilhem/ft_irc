/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: graux <marvin@42lausanne.ch>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 17:56:28 by graux             #+#    #+#             */
/*   Updated: 2023/11/19 12:08:48 by graux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"
#include <iostream>
#include <unistd.h>

Server::Server(void) //TODO Think about init values
{
}

Server::~Server(void)
{
	//TODO
	std::cerr << "Called Server destructor" << std::endl;
	close(sockfd);
}

Server::Server(Server const &s)
{
	*this = s;
}

Server &Server::operator=(Server const &s)
{
	if (this == &s)
		return (*this);
	password = s.password;
	port = s.port;
	return (*this);
}

Server::Server(std::string port_str, std::string pass) : password(pass), port(port_str)
{
	try {
		iport = std::stoi(port_str);
		if (iport < 1 || iport > 65535)
			throw std::invalid_argument("Invalid port number");
	}
	catch (std::exception &e) {
		std::cerr << "Invalid port number" << std::endl;
		exit(EXIT_FAILURE);
	}
	std::cout << *this;
}

void	Server::lnch(void)
{
	//TODO implement
	struct addrinfo hints = {};
	struct addrinfo *p;
	struct addrinfo	*servinfo;
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE;
	int status;
	if ((status = getaddrinfo(NULL, port.c_str(), &hints, &servinfo)) != 0)
	{
		std::cerr << "Error: getaddrinfo: " << gai_strerror(status);
		exit(1);
	}
	for (p = servinfo; p != NULL; p = p->ai_next)
	{
		if ((sockfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) == -1)
		{
			std::cerr << "Error: Socket" << std::endl;
			continue ;
		}
		int okay = 1;
		if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &okay, sizeof(int)) == -1)
		{
			std::cerr << "Error: setsockopt" << std::endl;
			exit(1);
		}
		if (bind(sockfd, p->ai_addr, p->ai_addrlen) == -1)
		{
			close(sockfd);
			std::cerr << "Error: bind" << std::endl;
			continue;
		}
		std::cout << "INFO: found a valid node, sockfd: " << sockfd << std::endl;
		break ;
	}
	freeaddrinfo(servinfo);
	if (!p)
	{
		std::cerr << "Error: Could nor find a binding" << std::endl;
		exit(1);
	}
}

void	Server::run(void)
{
	//TODO implement
}

std::string	Server::getPort(void) const
{
	return (port);
}

std::ostream &operator<<(std::ostream &o, const Server &s)
{
	o << "---------Server Stats---------\n";
	o << "port: " << s.getPort() << std::endl;
	return (o);
}
