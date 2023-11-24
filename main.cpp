/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppotier <ppotier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 15:42:49 by graux             #+#    #+#             */
/*   Updated: 2023/11/24 15:29:47 by ppotier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"
#include "Channel.hpp"
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
		serv.run();
	}
	else
	{
		std::cerr << "Usage: ./ircserv <port> <password>" << std::endl;
		return (1);
	}
	return (0);
}
