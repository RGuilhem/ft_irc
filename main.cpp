/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: graux <marvin@42lausanne.ch>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 15:42:49 by graux             #+#    #+#             */
/*   Updated: 2023/12/06 11:30:27 by graux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"
#include <iostream>
#include <sys/signal.h>

bool	server_off = false;

static void	signal_handler(int sig)
{
	(void) sig;
	server_off = true;
}

int	main(int argc, char *argv[])
{
	if (argc == 3)
	{
		signal(SIGINT, signal_handler);
		Server	serv(argv[1], argv[2]);
		serv.lnch();
		try {
			serv.run();
		} catch (std::exception &e) {
			std::cout << RESET_COL "Server shutdown" << std::endl;
		}
	}
	else
	{
		std::cerr << "Usage: ./ircserv <port> <password>" << std::endl;
		return (1);
	}
	return (0);
}
