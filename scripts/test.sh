#!/bin/bash
base_ip="10.105"
for i in $(seq 0 255); do
  # utilise printf pour construire l'adresse IP en utilisant l'adresse de base et l'incrément actuel
    for j in $(seq 0 255); do  
        ip=$(printf "$base_ip.%d.%d" $i $j)
        ./Snmp.sh -v "1" "$ip"
        #echo "$ip"
    done
done