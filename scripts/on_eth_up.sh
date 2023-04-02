#!/bin/bash

while [ 1 ]
do
	curl --silent --output /dev/null ifconfig.co
	if [[ $? -eq 0 ]]
	then
		echo "compilation capture/*.cpp"
		(cd /home/lbnf/lbnf/capture/ ; g++ *.cpp)
		echo "compilation terminee"
		echo "lancement capture"
		(cd /home/lbnf/lbnf/capture ; ./a.out)
		break
	fi
	sleep 1m

done
