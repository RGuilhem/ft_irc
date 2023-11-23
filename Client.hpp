/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: graux <marvin@42lausanne.ch>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 13:45:53 by graux             #+#    #+#             */
/*   Updated: 2023/11/23 11:49:13 by graux            ###   ########.fr       */
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
		int		    fd;
        std::string	read_buff;
        std::string	send_buff;
	public:
		Client(int fd);

		char	    *getReadBuffRaw(void);
		char	    *getSendBuffRaw(void);
        std::string getReadBuff(void) const;
        std::string getSendBuff(void) const;
};

#endif
