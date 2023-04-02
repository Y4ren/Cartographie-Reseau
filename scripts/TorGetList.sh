#!/bin/bash

while true 
do     
    let "a = `date +"%s"` % 1800"
    if [ $a = "0" ]
    then
        curl https://www.dan.me.uk/torlist/?exit > TorList.txt
        #curl https://check.torproject.org/exit-addresses | grep ExitAddress | cut -d' ' -f2 > TorList.txt
    else 
        sleep 1
    fi

done
