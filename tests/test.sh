#!/bin/bash

function slowcat(){ while read; do sleep .20; echo "$REPLY"; done; }

./ircserv 1500 test_pass &
pid=$!
sleep 1
cat ./tests/no_meaning.txt | slowcat | nc -c localhost 1500 > /dev/null &
cat ./tests/no_meaning.txt | slowcat | nc -c localhost 1500 > /dev/null &
sleep 5
kill -SIGKILL $pid
#todo kill process juste au cas ou...
