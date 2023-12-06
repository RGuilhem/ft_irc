# FT_IRC

## TODO
### General

- [x] handling of multiple clients
- [x] hostname and ip info for clients
- [x] Logging capability
- [x] client registration PASS NICK USER
- [x] PRIVMSG
	- [x] do not send to self
- [x] QUIT
- [x] Server replies
= [ ] hostname detection
= [ ] RPL numeric 004 remove placeolders
- [ ] Commands with list of arguments
- [x] Do not accept commands until registration complete
- [ ] A lot of testing
- [ ] irssi connection to server

### Channel

- [x] JOIN
- [x] PART
- [x] KICK
- [x] INVITE
- [ ] OPER
- [ ] WHO
- [x] TOPIC
- [x] MODE

### Bonus

- [ ] file transfer
- [ ] bot

## Ressources

https://modern.ircdocs.horse/
For irssi:
/connect -nocap -host localhost 127.0.0.1 1500 test guigui
