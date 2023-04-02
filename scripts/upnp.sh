#!/bin/bash

# Récupération de l'adresse IP
ip=$1

# Utilisation de la commande UPnP pour récupérer les informations de la machine
info=$(upnpc -l $ip 2>/dev/null)

# Vérification si l'IP est valide
if [ $? -ne 0 ]; then
  echo "L'adresse IP fournie est invalide ou la machine ne prend pas en charge UPnP."
  exit 1
fi

# Affichage des informations récupérées
echo "$info"

