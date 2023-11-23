#ifndef CHANNEL_HPP
# define CHANNEL_HPP

# include "Client.hpp"
# include <list>
# include <string>

class Channel
{
  private:
    std::string         name; //done;
    std::string         topic; //done;
    std::list<Client>   users; //done ??;
    std::list<Client>   operators; //todo;
    std::string         channelpassword; //done;

    bool                invite_only; //done;
    bool                topic_operator; //done;
    int                 user_limit; //done;
 	
	// ~Channel(); Destructeur ??
	// canonical form;
  public:
	/*GETERS*/
    Channel(void);
	Channel(std::string const &channelName);
	std::string const &		getTopic() const;
	std::string const&		getname() const;
	std::string const&		getchannelpassword() const;
	int						getuserlimit();
	bool 					getinviteonly();
	bool 					gettopicoperator();
};

#endif
