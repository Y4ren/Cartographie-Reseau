from libnmap.parser import NmapParser
import json

class MaClasseCustomService:
    def __init__(self):
        self.banner = [] 
        self.cpelist = []
        self.owner = []
        self.port = []
        self.protocol = []
        self.reason = []
        self.reason_ip = []
        self.reason_ttl = []
        self.scripts_results = []
        self.service = []
        self.state = []
        self.tunnel = []
class MaClasseCustomHost:
    def __init__(self, services : MaClasseCustomService()):
        self.address = []
        self.distance = []
        self.endtime = []
        self.starttime = []
        self.hostnames = []
        self.ipv4 = []
        self.ipv6 = []
        self.lastboot = []
        self.mac = []
        self.scripts_results = []
        self.status = []
        self.uptime = []
        self.vendor = []
        self.os_match = []
        self.services = []

class MaClasseCustomReport:
    def __init__(self, hosts : MaClasseCustomHost):
        self.startedstr = ""
        self.endtimestr = ""
        self.hosts_total = []
        self.hosts_up = []
        self.hosts_down = []
        self.numservices = []
        self.hosts = []

def loadFile(fileList):
    list = []

    for i in range(len(fileList)):
        nmapFile = NmapParser.parse_fromfile(fileList[i])
        list.append(nmapFile)

    return list


def nmapObjectToTab(nmapObj):

    a = MaClasseCustomReport([])

    a.endtimestr = nmapObj.endtimestr
    a.hosts_down.append(nmapObj.hosts_down)
    a.hosts_total.append(nmapObj.hosts_total)
    a.hosts_up.append(nmapObj.hosts_up)
    a.numservices.append(nmapObj.numservices)
    a.startedstr = nmapObj.startedstr

    for i in range(len(nmapObj.hosts)):
        a.hosts.append(MaClasseCustomHost([]))

    for i in range(len(nmapObj.hosts)):
        a.hosts[i].address.append(nmapObj.hosts[i].address)
        a.hosts[i].distance.append(nmapObj.hosts[i].distance)
        a.hosts[i].endtime.append(nmapObj.hosts[i].endtime)
        a.hosts[i].hostnames.append(nmapObj.hosts[i].hostnames)
        a.hosts[i].ipv4.append(nmapObj.hosts[i].ipv4)
        a.hosts[i].ipv6.append(nmapObj.hosts[i].ipv6)
        a.hosts[i].lastboot.append(nmapObj.hosts[i].lastboot)
        a.hosts[i].mac.append(nmapObj.hosts[i].mac)
        a.hosts[i].scripts_results.append(nmapObj.hosts[i].scripts_results)
        a.hosts[i].starttime.append(nmapObj.hosts[i].starttime)
        a.hosts[i].status.append(nmapObj.hosts[i].status)
        a.hosts[i].uptime.append(nmapObj.hosts[i].uptime)
        a.hosts[i].vendor.append(nmapObj.hosts[i].vendor)

        
        intermediar = nmapObj.hosts[i].os_match_probabilities()

        for k in range(len(intermediar)):
            tmp = intermediar[k].name + " " + str(intermediar[k].accuracy) + "%"
            cpes = intermediar[k].get_cpe()
            for cpe in cpes:
                tmp = tmp + " " + cpe
            a.hosts[i].os_match.append(tmp)

        for j in range(len(nmapObj.hosts[i].services)):
            a.hosts[i].services.append(MaClasseCustomService())

        for j in range(len(nmapObj.hosts[i].services)):
            a.hosts[i].services[j].banner.append(
                nmapObj.hosts[i].services[j].banner)
            a.hosts[i].services[j].cpelist.append(
                nmapObj.hosts[i].services[j].cpelist)
            a.hosts[i].services[j].owner.append(
                nmapObj.hosts[i].services[j].owner)
            a.hosts[i].services[j].port.append(
                nmapObj.hosts[i].services[j].port)
            a.hosts[i].services[j].protocol.append(
                nmapObj.hosts[i].services[j].protocol
            )
            a.hosts[i].services[j].reason.append(
                nmapObj.hosts[i].services[j].reason)
            a.hosts[i].services[j].reason_ip.append(
                nmapObj.hosts[i].services[j].reason_ip
            )
            a.hosts[i].services[j].reason_ttl.append(
                nmapObj.hosts[i].services[j].reason_ttl
            )
            a.hosts[i].services[j].scripts_results.append(
                nmapObj.hosts[i].services[j].scripts_results
            )
            a.hosts[i].services[j].service.append(
                nmapObj.hosts[i].services[j].service)
            a.hosts[i].services[j].state.append(
                nmapObj.hosts[i].services[j].state)
            a.hosts[i].services[j].tunnel.append(
                nmapObj.hosts[i].services[j].tunnel)

    return a


def addressIn(tab, address):
    for i in range(len(tab.hosts)):
        if address in tab.hosts[i].address:
            return i


def change(a, nmapObj):

    if nmapObj.hosts_down not in a.hosts_down:
        a.hosts_down.append(nmapObj.hosts_down)
    if nmapObj.hosts_total not in a.hosts_total:
        a.hosts_total.append(nmapObj.hosts_total)
    if nmapObj.hosts_up not in a.hosts_up:
        a.hosts_up.append(nmapObj.hosts_up)
    if nmapObj.numservices not in a.numservices:
        a.numservices.append(nmapObj.numservices)

    for i in range(len(nmapObj.hosts)):
        k = None
        k = addressIn(a, nmapObj.hosts[i].address)
        
        if k != None:
            if nmapObj.hosts[i].distance not in a.hosts[k].distance:
                a.hosts[k].distance.append(nmapObj.hosts[i].distance)
            if nmapObj.hosts[i].hostnames not in a.hosts[k].hostnames:
                a.hosts[k].hostnames.append(nmapObj.hosts[i].hostnames)
            if nmapObj.hosts[i].ipv4 not in a.hosts[k].ipv4:
                a.hosts[k].ipv4.append(nmapObj.hosts[i].ipv4)
            if nmapObj.hosts[i].ipv6 not in a.hosts[k].ipv6:
                a.hosts[k].ipv6.append(nmapObj.hosts[i].ipv6)
            if nmapObj.hosts[i].lastboot not in a.hosts[k].lastboot:
                a.hosts[k].lastboot.append(nmapObj.hosts[i].lastboot)
            if nmapObj.hosts[i].mac not in a.hosts[k].mac:
                a.hosts[k].mac.append(nmapObj.hosts[i].mac)
            if nmapObj.hosts[i].scripts_results not in a.hosts[k].scripts_results:
                a.hosts[k].scripts_results.append(
                    nmapObj.hosts[i].scripts_results)
            if nmapObj.hosts[i].status not in a.hosts[k].status:
                a.hosts[k].status.append(nmapObj.hosts[i].status)
            if nmapObj.hosts[i].uptime not in a.hosts[k].uptime:
                a.hosts[k].uptime.append(nmapObj.hosts[i].uptime)
            if nmapObj.hosts[i].vendor not in a.hosts[k].vendor:
                a.hosts[k].vendor.append(nmapObj.hosts[i].vendor)

            intermediar = nmapObj.hosts[i].os_match_probabilities()
            for l in range(len(intermediar)):
                tmp = intermediar[l].name + " " + str(intermediar[l].accuracy) + "%"
                cpes = intermediar[l].get_cpe()
                for cpe in cpes :
                    tmp = tmp + " " + cpe
                if (tmp not in a.hosts[k].os_match):
                    a.hosts[k].os_match.append(tmp)

            for j in range(len(nmapObj.hosts[i].services)):
                indice = None
                for l in range(len(a.hosts[k].services)):
                    if (nmapObj.hosts[i].services[j].port == a.hosts[k].services[l].port):
                        indice = l
                
                if(indice):
                    
                    if (
                        nmapObj.hosts[i].services[j].banner
                        not in a.hosts[k].services[indice].banner
                    ):
                        a.hosts[k].services[indice].banner.append(
                            nmapObj.hosts[i].services[j].banner
                        )

                    if (
                        nmapObj.hosts[i].services[j].cpelist
                        not in a.hosts[k].services[indice].cpelist
                    ):
                        a.hosts[k].services[indice].cpelist.append(
                            nmapObj.hosts[i].services[j].cpelist
                        )
                    if (
                        nmapObj.hosts[i].services[j].owner
                        not in a.hosts[k].services[indice].owner
                    ):
                        a.hosts[k].services[indice].owner.append(
                            nmapObj.hosts[i].services[j].owner
                        )
                    
                    if (nmapObj.hosts[i].services[j].port not in a.hosts[k].services[indice].port):
                        a.hosts[k].services[indice].port.append(
                            nmapObj.hosts[i].services[j].port
                        )

                    if (
                        nmapObj.hosts[i].services[j].protocol
                        not in a.hosts[k].services[indice].protocol
                    ):
                        a.hosts[k].services[indice].protocol.append(
                            nmapObj.hosts[i].services[j].protocol
                        )
                    
                    if (
                        nmapObj.hosts[i].services[j].reason
                        not in a.hosts[k].services[indice].reason
                    ):
                        a.hosts[k].services[indice].reason.append(
                            nmapObj.hosts[i].services[j].reason
                        )
                    if (
                        nmapObj.hosts[i].services[j].reason_ip
                        not in a.hosts[k].services[indice].reason_ip
                    ):
                        a.hosts[k].services[indice].reason_ip.append(
                            nmapObj.hosts[i].services[j].reason_ip
                        )
                    if (
                        nmapObj.hosts[i].services[j].reason_ttl
                        not in a.hosts[k].services[indice].reason_ttl
                    ):
                        a.hosts[k].services[indice].reason_ttl.append(
                            nmapObj.hosts[i].services[j].reason_ttl
                        )
                    if (
                        nmapObj.hosts[i].services[j].scripts_results
                        not in a.hosts[k].services[indice].scripts_results
                    ):
                        a.hosts[k].services[indice].scripts_results.append(
                            nmapObj.hosts[i].services[j].scripts_results
                        )
                    
                    if (
                        nmapObj.hosts[i].services[j].service
                        not in a.hosts[k].services[indice].service
                    ):
                        a.hosts[k].services[indice].service.append(
                            nmapObj.hosts[i].services[j].service
                        )
                    
                    if (
                        nmapObj.hosts[i].services[j].state
                        not in a.hosts[k].services[indice].state
                    ):
                        a.hosts[k].services[indice].state.append(
                            nmapObj.hosts[i].services[j].state
                        )
                    if (
                        nmapObj.hosts[i].services[j].tunnel
                        not in a.hosts[k].services[indice].tunnel
                    ):
                        a.hosts[k].services[indice].tunnel.append(
                            nmapObj.hosts[i].services[j].tunnel
                        )
        else:
            a.hosts.append(nmapObj.hosts[i])
    return a

def changeInNmapObjectList(a, listNmapObj):

    for obj in listNmapObj:
        change(a, obj)

    return a


def printInFile(report):
    
    data = {
        "startTime" : report.startedstr,
        "endTime": report.endtimestr,
        "totalHost": report.hosts_total,
        "hostUp": report.hosts_up,
        "hostDown": report.hosts_down,
        "numberOfService": report.numservices,
        "hosts": [
            {
                "address": host.address[0],
                "distance": host.distance,
                "endtime": host.endtime,
                "startTime": host.starttime,
                "hostname": host.hostnames[0],
                "IPV4": host.ipv4[0],
                "IPV6": host.ipv6[0],
                "lastBoot": host.lastboot,
                "MAC": host.mac,
                "scriptResult": host.scripts_results,
                "status": host.status,
                "uptime": host.uptime,
                "vendor": host.vendor,
                "osMatch": host.os_match,
                "services": [
                    {   
                        "serviceName": service.service,
                        "banner": service.banner,
                        "protocol": service.protocol,
                        "cpeList": service.cpelist,
                        "owner": service.owner,
                        "port": service.port,
                        "reason": service.reason,
                        "reasonIP": service.reason_ip,
                        "reasonTTL": service.reason_ttl,
                        "scriptsResult": service.scripts_results,
                        "state": service.state,
                        "tunnel": service.tunnel
                    }
                    for service in host.services
                ]
            }
            for host in report.hosts
        ]
    }
    with open("machine.json", "w") as f:
        json.dump(data, f)

# names = [
#     "/Users/landry/Desktop/lbnf/nmap_result/8a0a04499d2d4bb799c856346c9ec558",
#     "/Users/landry/Desktop/lbnf/nmap_result/63b0c7f14d3c4eca8a0a138a1f61130e",
#     "/Users/landry/Desktop/lbnf/nmap_result/68cd4f1079674fa8be70e767d2721172",
#     "/Users/landry/Desktop/lbnf/nmap_result/99d0f1451e2c4b5c8beccd37622f40dc",
#     "/Users/landry/Desktop/lbnf/nmap_result/8412c67f357940d785081e3432344300",
#     "/Users/landry/Desktop/lbnf/nmap_result/400748ebe95d47889b78b8e49f359838",
#     "/Users/landry/Desktop/lbnf/nmap_result/1211158dd6f047ee8c2b8dc7ec172ced"]
    
#    "/Users/landry/Desktop/lbnf/nmap_result/ee530c1b0c224a2e89624e1d161edf58"]

# names = [
#     "/home/valentin/dev/ESIEA/4A/PST/lbnf/nmap_result/2812c4a0a7314c08a9de6b0fb41c46d0",
#     "/home/valentin/dev/ESIEA/4A/PST/lbnf/nmap_result/4f087aad583c4b869729bedb16dc9755",
# #    "/home/valentin/dev/ESIEA/4A/PST/lbnf/nmap_result/50d97ed7e73d4ab98d15a004c2bfc022",
#     "/home/valentin/dev/ESIEA/4A/PST/lbnf/nmap_result/5181a7f3d02b4b979fea7cbae31e6500",
#     "/home/valentin/dev/ESIEA/4A/PST/lbnf/nmap_result/5be969d216fb47cea909d483932a1fdb",
#     "/home/valentin/dev/ESIEA/4A/PST/lbnf/nmap_result/70be6ee946e540c39912eb69f7e608c3",
#     "/home/valentin/dev/ESIEA/4A/PST/lbnf/nmap_result/8b7f18f4595f4f75ae47ed0ed6da2b59",
#     "/home/valentin/dev/ESIEA/4A/PST/lbnf/nmap_result/f959d2c8bfb24613b93c7e062dab5cec",
#     "/home/valentin/dev/ESIEA/4A/PST/lbnf/nmap_result/fe882be6209a45bba921cce2073aabe3"
# ]

# nmapObjList = loadFile(names)
# tab = nmapObjectToTab(nmapObjList[0])
# changeInNmapObjectList(tab, nmapObjList)
# printInFile(tab)
