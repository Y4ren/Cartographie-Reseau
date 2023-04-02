#install python 3.10.x via PPA Method

sudo apt update
#sudo apt install software-properties-common -y
sudo add-apt-repository ppa:deadsnakes/ppa -y
sudo apt update
sudo apt install python3.10 -y
python3.10 --version

#additional lib
sudo apt install python3.10-distutils -y

#install and upgrade pip
sudo apt install python3-pip
python3.10 -m pip install --upgrade pip
pip3.10 --version
