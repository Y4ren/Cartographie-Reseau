#!/bin/bash
if (( `python3 --version  | cut -d ' ' -f 2 | cut -d '.' -f 2` >= 10))
    then 
        echo "python 3.10 or higher already installed"
    else 
        echo "pleas install python 3.10 or higher"
        exit 0
fi 

#install python dependencies
python3 -m pip install -r PY-REQUIREMENTS.txt


#check and install node
if which node > /dev/null
    then 
        echo "node is already installed"
    else
        if [[ "$OSTYPE" == "linux-gnu"* ]]; then
            sudo apt install nodejs
        elif [[ "$OSTYPE" == "darwin"* ]]; then
            brew install node
        fi
fi

#check node version
if (( `node -v | cut -c 2-3` >= 18))
    then 
        echo "node >= 18 already installed"
    else   
        echo "Node version 18 or higher is required"
        exit 0
fi

# check and install npm
if which npm > /dev/null
    then 
        echo "npm is already installed"
    else
        if [[ "$OSTYPE" == "linux-gnu"* ]]; then
            sudo apt install npm
        elif [[ "$OSTYPE" == "darwin"* ]]; then
            brew install npm
        fi
fi 

#check and install libjson-cpp
if [[ "$OSTYPE" == "linux-gnu"* && ! `dpkg --list | grep libjsoncpp-dev` ]]; then
    sudo apt install libjsoncpp-dev
elif [[ "$OSTYPE" == "darwin"* && ! `brew list | grep jsoncpp` ]]; then
    brew install jsoncpp
fi

#install pakage for node
cd Web/
npm install
cd .. 

#compile the sources
./capture/compile.sh
