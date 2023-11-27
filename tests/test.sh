#!/bin/bash

function slowcat(){ while read; do sleep .20; echo "$REPLY"; done; }

./ircserv 1500 test_pass &
pid=$!
sleep 1
osname=$(uname)
darwin="Darwin"
if [ "$osname" = "$darwin" ];
then
	cat ./tests/channel_u1.txt | slowcat | nc -c localhost 1500 > ./tests/valid_auth.log &
	sleep 0.2
	cat ./tests/channel_u2.txt | slowcat | nc -c localhost 1500 > ./tests/valid_auth.log &
else
	cat ./tests/valid_auth.txt | slowcat | nc -C localhost 1500 > ./tests/valid_auth.log &
fi
sleep 5
cat serv.log
kill -SIGINT $pid
#todo kill process juste au cas ou...
