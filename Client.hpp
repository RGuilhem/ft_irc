/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: graux <marvin@42lausanne.ch>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 13:45:53 by graux             #+#    #+#             */
/*   Updated: 2023/12/05 16:55:09 by graux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_HPP
# define CLIENT_HPP

# include <string>

class Client
{
	private:
		bool		correct_pass;
		bool		is_registered;
		std::string nickname;
		std::string	username;
		std::string realname;
		std::string	hostname;
		int		    fd;
		std::string	read_buff;
		std::string	send_buff;
	public:
		Client(int fd);
		~Client();
		bool	operator==(Client const &other) const;

		void		appendRead(std::string newData);
		std::string	nextRead(void) const;
		void		clearNextRead(void);
		void		appendSend(std::string newData);
		void		resetReadBuff(void);
		void		clearEndReadBuff(void);
		void		clearSentSendBuff(int sent);

		void		checkRegistration(void);

		std::string getReadBuff(void) const;
		std::string getSendBuff(void) const;
		bool		getCorrectPass(void) const;
		void		setCorrectPass(bool val);
		bool		getRegistered(void) const;
		void		setRegistered(bool val);
		std::string	getId(void) const;
		std::string	getNickname(void) const;
		void		setNickname(std::string const &val);
		std::string	getUsername(void) const;
		void		setUsername(std::string const &val);
		std::string	getRealname(void) const;
		void		setRealname(std::string const &val);
};

#endif
