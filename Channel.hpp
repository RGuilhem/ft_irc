#ifndef CHANNEL_HPP
# define CHANNEL_HPP

# include "Client.hpp"
# include <list>
# include <string>

class Channel
{
  private:
    std::string         name;
    std::string         topic;
    std::list<Client>   users;
    std::list<Client>   operators;

    bool                invite_only;
    bool                topic_operator;
    std::string         password;
    int                 user_limit;

    Channel(void);
  public:
};

#endif
