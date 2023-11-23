/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppotier <ppotier@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 15:42:49 by graux             #+#    #+#             */
/*   Updated: 2023/11/23 14:01:13 by ppotier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"
#include "Channel.hpp"
#include <iostream>

bool	server_off = false;

// int	main(int argc, char *argv[])
// {
// 	if (argc == 3)
// 	{
// 		Server	serv(argv[1], argv[2]);
// 		serv.lnch();
// 		serv.run();
// 	}
// 	else
// 	{
// 		std::cerr << "Usage: ./ircserv <port> <password>" << std::endl;
// 		return (1);
// 	}
// 	return (0);
// }

int main (int ac, char **av)
{
	(void)ac;
	(void)av;
	Channel a("themes");
	std::cout << a.getuserlimit() << std::endl;
	return 0;
}