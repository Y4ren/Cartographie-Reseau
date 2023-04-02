#!/bin/bash


path="/home/lbnf/lbnf"
source $path/scripts/config.sh



if [[ $_FIRST_LAUNCH -eq "true" ]]
then

	create_user () {

		curl -s -XPOST -H "Content-Type: application/json" -d '{
  		"name":"lbnf",
  		"email":"lbnf@lbnf.com",
  		"login":"lbnf",
  		"password":"lbnf"
		}' http://admin:admin@localhost:3000/api/admin/users >/dev/null

	}

fi

#start grafana
sudo systemctl daemon-reload
sudo systemctl start grafana-server
#sudo systemctl status grafana-server

create_user 2>/dev/null

sudo systemctl start nginx

if [[ $? -eq 0 ]]
then
	echo -e "\033[31mServeur lancé sur http://localhost:3000 ou http://$ip:3000"
fi
