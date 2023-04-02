#!/bin/bash

show_help()
{
    echo "Usage: snmp.h -c COMUNITY_STRING
              -v VERISON (1 or 2c)
              IP address"
    exit 1
}

string="public"
version=0

while getopts ":h?:p:c:v:" option
do
    case $option in
        v)
            if [[ "$OPTARG" != "1" && "$OPTARG" != "2c" ]]
            then
                echo "Wrong version"
                show_help
            fi
            version=$OPTARG
        ;;
        c)
            string=$OPTARG
            ;;      
        :)
            echo "L'option $OPTARG requiert un argument"
            show_help
            ;;
        h|\?)
            echo "unrecognized argument $OPTARG"
            show_help
            ;;
    esac
done

if [ $OPTIND -eq 1 ] 
then 
    show_help 
fi

shift $((OPTIND-1))

snmpwalk -v$version -c $string $1 1.3.6.1.2.1.1.1.0
snmpwalk -v$version -c $string $1 1.3.6.1.2.1.1.3.0
exit 0
