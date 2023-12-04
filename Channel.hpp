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
		unsigned int		user_limit;

		Channel(void);
	public:
		Channel(std::string const &name, Client &creator);

		std::string getName(void) const;
		std::string getTopic(void) const;
		void        join(Client &client, std::string pass);

		std::vector<std::string> getUsersNicks(void) const;
};

#endif
