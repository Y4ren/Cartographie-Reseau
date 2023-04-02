#!/bin/bash
echo -e "\x1B[31m\x1B[1mThis script shood be run from the parent directory /lbnf\x1B[21m\x1B[39m"
if [[ "$OSTYPE" == "linux-gnu"* ]]; then
    # ...
    g++ $(find capture/src -name '*.cpp') -Wall -ljsoncpp -lpcap -o lbnf
    #docker-compose -f docker-install/docker-compose.yml up
elif [[ "$OSTYPE" == "darwin"* ]]; then
    # Mac OSX
    g++ -std=c++17 $(find capture/src -name '*.cpp') -Wall -lpcap -ljsoncpp -o lbnf
    #docker-compose -f docker-install/docker-compose.yml up
fi

if [[ $? == 0 ]] ; then
    echo -e "\x1B[32m\x1B[1mCompile complete\x1B[21m\x1B[39m"
else
    echo -e "\x1B[31m\x1B[1mCompile failed\x1B[21m\x1B[39m"
fi