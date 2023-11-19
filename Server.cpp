/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: graux <marvin@42lausanne.ch>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 17:56:28 by graux             #+#    #+#             */
/*   Updated: 2023/11/19 10:59:17 by graux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"
#include <iostream>

Server::Server(void) //TODO Think about init values
{
}

Server::~Server(void)
{
	//TODO
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

Server::Server(std::string port_str, std::string pass) : password(pass)
{
	try {
		port = std::stoi(port_str);
		if (port < 1 || port > 65535)
			throw std::invalid_argument("Invalid port number");
	}
	catch (std::exception &e) {
		std::cerr << "Invalid port number" << std::endl;
		exit(EXIT_FAILURE);
	}
}
