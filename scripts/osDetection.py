import string
import json

class OSDetection:

# Print the os type for a given ttl from osTtl.json (you can give ttl only or ttl + protocol)
    def ttlSearch(self, ttl:string, protocol:string = "NULL")->None: 
        if protocol == "NULL":
            with open('./osTtl.json', 'r') as f:
                osTtl = json.load(f)
            try:
                print(osTtl["General"][ttl]["OS"])
            except KeyError:
                print("ttl non référencé")

        else:
            with open('./osTtl.json', 'r') as f:
                osTtl = json.load(f)
            try:
                print(osTtl["Protocole"][protocol][ttl]["OS"])
            except KeyError:
                print("TTl ou protocole non référencé")