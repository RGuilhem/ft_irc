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

    Channel(void);
  public:
};

#endif
