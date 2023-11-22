/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: graux <marvin@42lausanne.ch>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 13:45:53 by graux             #+#    #+#             */
/*   Updated: 2023/11/22 23:14:26 by graux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_HPP
# define CLIENT_HPP

#define BUFF_SIZE 512

class Client
{
	private:
		int		fd;
		char	read_buff[BUFF_SIZE];
		char	send_buff[BUFF_SIZE];
	public:
		Client(int fd);

		char	*getReadBuff(void);
		char	*getSendBuff(void);
};

#endif
