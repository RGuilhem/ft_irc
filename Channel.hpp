#ifndef CHANNEL_HPP
# define CHANNEL_HPP

# include "Client.hpp"
# include <vector>
# include <string>

class Channel
{
	private:
		std::string         name;
		std::string         topic;
		std::vector<Client>   users;
		std::vector<Client>   operators;
		std::vector<Client>   invited;
		std::vector<Client>   banned;

		bool                invite_only;
		bool                topic_operator;
		std::string         password;
		int					user_limit;

		Channel(void);
		void addMode(char mode, std::string arg);
		void delMode(char mode);
	public:
		Channel(std::string const &name, Client &creator);

		std::string getName(void) const;
		std::string getTopic(void) const;
		void        join(Client &client, std::string pass);
		void		greet(Client &client);

		std::vector<std::string> getUsersNicks(void) const;
		bool	isInChannel(Client const &client) const;
		bool	isOperator(Client const &client) const;
		bool	getInviteOnly(void) const;
		void	invite(Client &client);
		void	removeFromChannel(Client const &client);
		std::string	modeString(void) const;
		void changeMode(std::vector<std::string> args, Client &client);
};

#endif
