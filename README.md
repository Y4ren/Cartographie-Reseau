# LBNF

## Table of Contents

- [LBNF](#lbnf)
	- [Table of Contents](#table-of-contents)
	- [A propos](#a-propos)
	- [Telechargement](#telechargement)
	- [Installation](#installation)
		- [Quick start](#quick-start)
	- [Utilisation](#utilisation)
	- [Services](#services)
	- [Tâches à realiser](#tâches-à-realiser)
- [Hiérarchie des fichiers](#hiérarchie-des-fichiers)

## A propos

Projet de cartographie réseau passive (et prochainement active) utilisant
python et le projet open-source Grafana.

Fork du projet original pour l'adapater sur Rasperry pi.

## Telechargement

Avec **HTTP** : 
```sh
git clone https://gitlab.com/pst4-cartographie-reseaux/lbnf.git
```

Avec **SSH** : 
```sh
git clone git@gitlab.com:pst4-cartographie-reseaux/lbnf.git
```

## Installation

*Se deplacer dans le dossier du projet*

```sh
cd path/to/lbnf-raspberry
```


*Installer python si ce n'est pas déjà fait*

```sh
sudo ./python3.10Install.sh
```

*Lancer le script d'installation*

```sh
sudo ./install.sh
```

*Compiler les sources*

```
./capture/install.sh
```

*Lancer le serveur Web et la capture*

```sh
sudo ./run.sh
```

### Quick start

```sh
git clone https://gitlab.com/pst4-cartographie-reseaux/lbnf.git
cd lbnf
sudo ./install.sh
./capture/install.sh
```

***

## Utilisation

Se rendre à l'adresse : http://localhost:3000 ou http://@IP_machine:3000

Si tout s'est bien passé, vous devriez arriver sur la page de connexion de Grafana :

![Page de connexion Grafana](https://i.stack.imgur.com/F5YMp.png)


## Services

Port  | Service
----- | --------
3000  | Grafana
3001  | Nginx

## Tâches à realiser

- [ ] Script Scan passif
	- [x] Detection OS avec les TTL
	- [x] Trier adresses de broadcast
	- [x] Reecriture du script
		- [x] Optimisation 
		- [x] Creation des Noeuds
		- [x] Creation des Arcs
	- [x] Mise a jour des noeuds TOR automatique
	- [x] Prendre en entrée des fichier .PCAP

- [ ] Data Visualisation avec Grafana
	- [x] Visualisation en temps reel
	- [x] Noeuds
	- [x] Nombre de paquets
		- [x] Couplage avec les nombre d'octets
	- [x] Afficher les appareils apparus / disparus
	- [x] Importer automatiquement un dashboard
	- [x] Créer des utilisateurs
	- [x] Nginx Server

- [ ] Portage sur Raspberry
	- [x] Script de lancement automatique
	- [x] Verification de connexion au LAN	

- [ ] C++ : auto-merge -> simplification (liste simple)

- [ ] Fusion passif<=>active

- [ ] Parseur XML

# Hiérarchie des fichiers
<pre>
📁
├──📁Active
│   ├── activeDetection.py
│   ├── Command.json
│   ├── MergerXML.py
│   └──📁__pycache__
│
├──📁capture
│   ├── compile.sh <span style="color:green">//Compile les sources</span>
│   └──📁src
│       ├──📁application <span style="color:green">//Contient les parseurs des protocoles de la couche application</span>
│       │   ├── DNS.cpp
│       │   ├── DNS.h
│       │   ├── HTTP.cpp
│       │   ├── HTTP.h
│       │   ├── MDNS.cpp
│       │   ├── MDNS.h
│       │   ├── QUIC.cpp
│       │   └── QUIC.h
│       ├──📁data-link <span style="color:green">//Contient les parseurs des protocoles de la couche data-link</span>
│       │   ├── ethernet.cpp
│       │   └── ethernet.h
│       ├──📁network <span style="color:green">//Contient les parseurs des protocoles de la couche network</span>
│       │   ├── ICMPv4.cpp
│       │   ├── ICMPv4.h
│       │   ├── ICMPv6.cpp
│       │   ├── ICMPv6.h
│       │   ├── IPv4.cpp
│       │   ├── IPv4.h
│       │   ├── IPv6.cpp
│       │   └── IPv6.h
│       ├──📁presentation <span style="color:green">//Contient les parseurs des protocoles de la couche présentation</span>
│       │   ├── TLS.cpp
│       │   └── TLS.h
│       ├──📁session <span style="color:green">//Contient les parseurs des protocoles de la couche session</span>
│       │   ├── SMB.cpp
│       │   └── SMB.h
│       ├──📁transport <span style="color:green">//Contient les parseurs des protocoles de la couche transport</span>
│       │   ├── ports.h
│       │   ├── TCP.cpp
│       │   ├── TCP.h
│       │   ├── UDP.cpp
│       │   └── UDP.h
│       ├── active.cpp <span style="color:green">//Code contenant la partie active</span>
│       ├── active.hpp
│       ├── main.cpp
│       ├── manager.cpp <span style="color:green">//Classe "statique" gérant les nodes</span>
│       ├── manager.hpp
│       ├── node.cpp <span style="color:green">//Classe Node qui représente les machines</span>
│       ├── node.hpp
│       ├── UI.cpp <span style="color:green">//Classe "statique" UI qui gère l'interface utilisateur</span>
│       └── UI.hpp
│
├──📁docker-install
│   ├── docker-compose.yml
│   ├── dockerfile
│   ├──📁grafana-conf
│   │   ├── grafana.ini
│   │   ├── ldap.toml
│   │   └──📁provisioning
│   │       ├──📁dashboards
│   │       │   ├── dashboard.json
│   │       │   └── dashboard.yaml
│   │       └──📁datasources
│   │           └── datasource.yaml
│   └── nginx.conf
├── install.sh
├── nmap_result
├── PY-REQUIREMENTS.txt
├── README.md
└──📁scripts
    ├── config.sh
    ├── on_eth_up.sh
    ├── on_eth_up.sh.save
    ├── osDetection.py
    ├── osTtl.json
    ├── python3.10Install.sh
    ├── Snmp.sh
    ├── startGraphana.sh
	├── test.sh
	├── upnp.sh
    └── TorGetList.sh
</pre>
