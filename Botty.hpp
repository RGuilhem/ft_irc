/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Botty.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: graux <marvin@42lausanne.ch>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 19:02:10 by graux             #+#    #+#             */
/*   Updated: 2023/12/11 06:38:24 by graux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BOTTY_HPP
# define BOTTY_HPP

# include "Client.hpp"
# include <string>
# include <vector>
# include <map>
# include <cstdlib>
# include <ctime>

class Botty
{
	typedef void (Botty::*Exec_func)(Client &, std::string , std::vector<std::string>);
	typedef std::map<std::string, Exec_func> CommMap;
	private:
		void		sendMsg(Client &client, std::string message);
		static CommMap	commands_map;
		static CommMap	init_commands_map(void);
		static bool	isCommand(std::string comm);
	public:
		Botty(void);
		~Botty(void);

		std::string	greet(void) const;
		std::string	getNickname(void) const;
		void		handleMsg(Client &client, std::string message);

		void		help(Client &client, std::string command, std::vector<std::string> args);
		void		coinflip(Client &client, std::string command, std::vector<std::string> args);
		void		list(Client &client, std::string command, std::vector<std::string> args);
};

#endif
