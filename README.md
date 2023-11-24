# FT_IRC

Docs ::
	https://github.com/marineks/Ft_irc
	https://tools.ietf.org/html/rfc1459 Protocol
	https://tools.ietf.org/html/rfc2810 Architecture
	https://tools.ietf.org/html/rfc2811 Channel Management
	https://tools.ietf.org/html/rfc2812 Client
	https://tools.ietf.org/html/rfc2813 Server Protocol
	https://tools.ietf.org/html/rfc7194 Default Port for Internet Relay Chat (IRC) via TLS/SSL

Un channel est crée si un client join le channel, et devient obligatoirement Operator du chan;
L'operateur doit avoir un '@' devant son username;
Operator command :
	KICK, enleve un client du channel;
	INVITE, invite un client au chan;
	TOPPIC, change ou check le themes du channel;
	MODE, change le mode du channel :
			i, mettre/enlever invite only du chan;
			t, mettre/enlever les restrictions du themes par le channel operator;
			k, mettre/enlever le mot de passe acces au chan;
			o, donne/suppr le mode operator d'un user;
			l, metter/enlever le nbr de user max d'un chan;

pour MACOS:
		on doit utiliser fcntl de cette maniere:
			fcntl(fd, F_SETFL, O_NONBLOCK);

./ircserv <port> <password> <- l'executable;

Le MDP est obliagtoire pour chaque nouveau client qui se co au serv;

On doit utiliser UN seul poll() ou équivalent :
		read, write, listen;
	pour select(), kqueue() et epoll(), c'est flou, avons nous le droit qu'a un seul ?
 
Signal ????

Le channel est suppr quand le dernier client leave;
Les channels names ne doivent pas depasser 200characters selon la norme IRC;
Les channels names comment par '&' ou '#', ne doit pas contenir ' ', '^G' (ascii 7) ou ',';
Un client ne doit pas avoir plus de 10clients a son actif;

Les messages ne doivent pas depasser 512 carateres, avec le RETURN inclus (donc 510 + '\n');
## TODO
### General

- [x] handling of multiple clients
- [ ] hostname and ip info for clients
- [ ] Logging capability
- [ ] client registration PASS NICK USER
- [ ] PRIVMSG
- [ ] Server replies

### Channel

- [ ] message forwarding
- [ ] operators
- [ ] KICK
- [ ] INVITE
- [ ] TOPIC
- [ ] MODE
- [ ] Config file for default channels and operators

### Bonus

- [ ] file transfer
- [ ] bot
