#!/bin/bash

function slowcat(){ while read; do sleep .20; echo "$REPLY"; done; }

./ircserv 1500 test_pass &
pid=$!
sleep 1
osname=$(uname)
darwin="Darwin"
if [ "$osname" = "$darwin" ];
then
    option="-c"
else
    option="-C"
fi
cat ./tests/botty.txt | slowcat | nc $option localhost 1500 > /dev/null &
sleep 5
kill -SIGINT $pid
#todo kill process juste au cas ou...
