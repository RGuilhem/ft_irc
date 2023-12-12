# FT_IRC

## TODO

### For eval
	Networking

   - [x] The server starts, and listens on all network interfaces on the port given from the command line.
   - [x] Using the 'nc' tool, you can connect to the server, send commands, and the server answers you back.
   - [x] Using this IRC client, you can connect to the server.
   - [x] The server can handle multiple connections at the same time. The server should not block. It should be able to answer all demands. Do some test with the IRC client and nc at the same time.
   - [x] Join a channel thanks to the appropriate command. Ensure that all messages from one client on that channel are sent to all other clients that joined the channel.

	Networking special

   - [ ] Just like in the subject, using nc, try to send partial commands. Check that the server answers correctly. With a partial command sent, ensure that other connections still run fine.
   - [ ] Unexpectedly kill a client. Then check that the server is still operational for the other connections and for any new incoming client.
   - [ ] Unexpectedly kill a nc with just half of a command sent. Check again that the server is not in an odd state or blocked.
   - [ ] Stop a client (^-Z) connected on a channel. Then flood the channel using another client. The server should not hang. When the client is live again, all stored commands should be processed normally. Also, check for memory leaks during this operation.

	Client commands basic

   - [ ] With both nc and the reference IRC client, check that you can authenticate, set a nickname, a username, join a channel. This should be fine (you should have already done this previously).
   - [ ] Verify that private messages (PRIVMSG) are fully functional with different parameters.

	Client commands operators
	
	- [ ] All five

### General

- [x] handling of multiple clients
- [x] hostname and ip info for clients
- [x] Logging capability
- [x] client registration PASS NICK USER
- [x] PRIVMSG
	- [x] do not send to self
- [x] QUIT
- [x] Server replies
- [x] RPL numeric 004 remove placeolders
- [x] Do not accept commands until registration complete
- [ ] A lot of testing
- [x] irssi connection to server
- [ ] abort trap 6 on ^C ???

### Channel

- [x] JOIN
- [x] PART
	- [ ] delete chan if empty?
- [x] KICK
- [x] INVITE
- [x] WHO
- [x] TOPIC
- [x] MODE
	- [ ] o in MODE ???

### Bonus

- [ ] file transfer
- [x] bot

## Ressources

https://modern.ircdocs.horse/
For irssi:
/connect -nocap -host localhost 127.0.0.1 1500 test guigui
