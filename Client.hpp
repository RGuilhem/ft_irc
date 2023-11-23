/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: graux <marvin@42lausanne.ch>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 13:45:53 by graux             #+#    #+#             */
/*   Updated: 2023/11/23 00:31:46 by graux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_HPP
# define CLIENT_HPP

#define BUFF_SIZE 512

# include <string>

class Client
{
	private:
        std::string nick;
        std::string name;
		int		fd;
		char	read_buff[BUFF_SIZE];
		char	send_buff[BUFF_SIZE];
	public:
		Client(int fd);

		char	*getReadBuff(void);
		char	*getSendBuff(void);
};

#endif
