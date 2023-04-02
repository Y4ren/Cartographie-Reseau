import sys
import os
import re
import string
import datetime
import platform
import json
from subprocess import run, DEVNULL
from termcolor import colored, cprint
import uuid
import mergerXML

class Scan:
    scan = ["-sS", "-sT", "-sW", "-sM", "-sU", "-sN", "-sF", "-sX"]

    def scanIteration(self, command: list, names: list) -> None:
        """Iterate every type of scan and outputs files for a command and run it"""

        for scan, name in zip(Scan().scan, names):
            tmp = [scan, "-oX", name]
            cmd = run(command + tmp)

            if cmd.returncode != 0:
                sys.exit(colored(
                    "Something wrong happened with the nmap shell command", "yellow", attrs=["bold"],))
        return


class Ping:
    ping = ["-PS", "-PA", "-PU", "-PY", "-PE", "-PP", "-PM"]

    def pingIteration(self, command: list, names: list) -> None:
        """Iterate every type of ping for a command and run it"""

        for ping, name in zip(Ping().ping, names):
            tmp = [ping, "-oX", name]
            cmd = run(command + tmp)

        if cmd.returncode != 0:
            sys.exit(colored(
                "Something wrong happened with the nmap shell command", "yellow", attrs=["bold"],))
        return


class activeDetection:

    def menu(self, category: str) -> dict():
        """Displays options of the choosen category and returns the json loaded"""

        with open("./Active/Command.json", "r") as f:
            menu = json.load(f)

        try:
            for i in range(len(menu[category])):
                print(menu[category][i][0] + " : " + str(i + 1))

        except KeyError:
            sys.exit(colored("Internal error", "red", attrs=["bold", "blink"]))

        return menu

    def platformDetetction(self) -> str():
        """Return the appropriate PATH for nmap regarding the platform"""

        platformName = platform.uname().system

        if platformName == "Darwin":
            return "/usr/local/bin/nmap"

        elif platformName == "Linux":
            return "/bin/nmap"

        else:
            sys.exit(colored("Windows not supported", "red", attrs=["bold", "blink"]))

    def choiceCheck(self, choix: str, menu: dict,  category: str = None) -> None:
        """Test the input validity of the user"""
        if category:
            if choix not in str(list(range(1, len(menu[category]) + 1))):
                sys.exit(
                    colored("The option you selected does not exist", "yellow", attrs=["bold"]))
        else:
            if choix not in str(list(range(1, len(menu) + 1))):
                sys.exit(
                    colored("The option you selected does not exist", "yellow", attrs=["bold"]))
        return

    def testIP(self, choix: str, iP: str) -> None:
        """Test the validity of the IP@ regarding the choosen type of scan"""

        regex = r"^(?:[0-9]{1,3}\.){3}[0-9]{1,3}$" if choix == "1" else r"^([0-9]{1,3}\.){3}[0-9]{1,3}(\/([0-9]|[1-2][0-9]|3[0-2]))?\s*$"

        if not re.search(regex, iP):
            sys.exit(colored("Your IP address is not valid \n", "yellow", attrs=["bold"]))

    def testDirectory(self, excludeFilePath: str) -> None:
        try:
            file = open(excludeFilePath)
            file.close()
            return
        except FileNotFoundError:
            sys.exit(colored(
                "The file from the path does not exist \n", "yellow", attrs=["bold"],))
        except IsADirectoryError:
            sys.exit(colored(
                "The path is a directory \n", "yellow", attrs=["bold"],))

    def commandConstruct(self, menu: dict, category: str, choix: str, nmapPath: str, iP: str) -> list:
        """Build the choosen command and returns it"""

        command = ["sudo", nmapPath, iP]
        try:
            command.extend(menu[category][int(choix) - 1][1].split(" "))

        except (IndexError, ValueError, TypeError):
            sys.exit(colored("The value entered is invalid\n", "yellow", attrs=["bold"]))

        return command

    def addOptions(self, command: list, excludeFilePath: str = None, portNum: str = None) -> list:
        """Add the option to add a file with IP and port number to exclude"""

        if excludeFilePath:
            command.extend(["--excludefile", excludeFilePath])

        if portNum:
            regex = r'^((6553[0-5])|(655[0-2][0-9])|(65[0-4][0-9]{2})|(6[0-4][0-9]{3})|([1-5][0-9]{4})|([0-5]{0,5})|([0-9]{1,4}))$'
            regex2 = r'/^((6553[0-5])|(655[0-2][0-9])|(65[0-4][0-9]{2})|(6[0-4][0-9]{3})|([1-5][0-9]{4})|([0-5]{0,5})|([0-9]{1,4}))-((6553[0-5])|(655[0-2][0-9])|(65[0-4][0-9]{2})|(6[0-4][0-9]{3})|([1-5][0-9]{4})|([0-5]{0,5})|([0-9]{1,4}))$'

            if not re.search(regex, portNum) and not re.search(regex2):
                sys.exit(colored(
                    "Your address or port number is not valid\n", 'yellow', attrs=["bold"]))
            command.extend(["-p" + portNum])
        return command

    def scanUniqMachine(self, iP: str) -> list:
        """Execute the scan for a unique machine"""

        nmapPath = self.platformDetetction()

        # Creation of uniq name for each scan
        names = [str("nmap_result/" + uuid.uuid4().hex) for x in range(len(Scan.scan))]

        # Dysplay of the scan option
        menu = self.menu("Scan specific machine")

        choix = input("Select the scan you want to execute\n")

        self.choiceCheck(choix, menu, "Scan specific machine")

        command = self.commandConstruct(
            menu, "Scan specific machine", choix, nmapPath, iP)

        print(colored("Commande nmap :" + str(command), "blue", attrs=["bold"]))

        # execution of all the type of scan on the choosen IP
        Scan().scanIteration(command, names)
        return names

    def scanNetwork(self, iP: str, excludeFilePath: str = None) -> list:
        """Execute a scan on a network with options given in parameter"""

        nmapPath = self.platformDetetction()

        # Dysplay scan options
        menu = self.menu("Scan network")

        choix = input("Select the scan you want to execute\n")

        self.choiceCheck(choix, menu, "Scan network")

        command = self.commandConstruct(
            menu, "Scan network", choix, nmapPath, iP)

        # if the user decide to scan a specific/range port we need to iterate throught the scans and not the ping method
        if (menu["Scan network"][int(choix)-1][0] == "Scan specific port and service detection"):
            # Creation of uniq name for each scan
            names = [str("nmap_result/" + uuid.uuid4().hex) for x in range(len(Scan.scan))]

            if (input("Do you want to specify a port number or a range of port to scan [NO/yes]\n") == "yes"):
                portNum = input(
                    "Enter the number of the port you want to scan or the range of port you want to scan\n")

            command = self.addOptions(command, excludeFilePath, portNum)

            print(colored("Commande nmap :" + str(command), "blue", attrs=["bold"]))
            print(colored("\nStarting the port scan\n", "green", attrs=["bold"]))
            Scan().scanIteration(command, names)

        else:
            # Creation of uniq name for each scan
            names = [str("nmap_result/" + uuid.uuid4().hex) for x in range(len(Ping.ping))]

            command = self.addOptions(command, excludeFilePath)

            # execute all the type of ping on the specified network
            print(colored("Commande nmap :" + str(command), "blue", attrs=["bold"]))
            print(colored("\nStarting the discovery of the network\n", "green", attrs=["bold"]))

            Ping().pingIteration(command, names)
        return names

    def scanCustom(self, iP: str, excludeFilePath: str = None) -> list:
        """Execute custom command wrote by the user in the custom Command.json section and ask for ping or scan iteration"""

        nmapPath = self.platformDetetction()

        menu = self.menu("Custom")

        choix = input("Select the scan you want to execute\n")

        self.choiceCheck(choix, menu, "Custom")

        command = self.commandConstruct(menu, "Custom", choix, nmapPath, iP)

        if (input("Do you want to specify a port number or a range of port to scan [NO/yes]\n") == "yes"):
            portNum = input(
                "Enter the number of the port you want to scan or the range of port you want to scan\n")

        # Creation of uniq name for each scan
        names = [str("nmap_result/" + uuid.uuid4().hex) for x in range(len(Ping.ping))]

        command = self.addOptions(command, excludeFilePath, portNum)

        print(colored("Commande nmap :" + str(command), "blue", attrs=["bold"]))

        choix = input("Do you want to iterate ping : 1 or scan : 2")

        if (choix == "1"):
            Ping().pingIteration(command, names)
        elif (choix == "2"):
            Scan().scanIteration(command, names)
        else:
            sys.exit(colored("The option you selected does not exist", "yellow", attrs=["bold"]))

        return names


if __name__ == "__main__":
    try:
        a = activeDetection()

        menu = ["Scan specific machine", "Scan network", "Custom"]

        for i in range(len(menu)):
            print(menu[i] + " : " + str(i + 1))

        choix = input("Choose the category you want\n")

        a.choiceCheck(choix, menu)

        iP = input("Choose the IP or range of IP you want to scan (CIDR notaion)\n")

        a.testIP(choix, iP)

        if choix == "1":
            names = a.scanUniqMachine(iP)
        else:
            excludeFilePath = None
            if (input("Do you want to add a file of IP adress to exclude [NO / yes]\n") == "yes"):
                excludeFilePath = input("Enter the path of the file containing the list of IP you want to exclude\n")
                a.testDirectory(excludeFilePath)

            if choix == "2":
                names = a.scanNetwork(iP, excludeFilePath)

            elif choix == "3":
                names = a.scanCustom(iP, excludeFilePath)

        nmapObjList = mergerXML.loadFile(names)
        tab = mergerXML.nmapObjectToTab(nmapObjList[0])
        mergerXML.changeInNmapObjectList(tab, nmapObjList)
        mergerXML.printInFile(tab)

    except KeyboardInterrupt:
        sys.exit(colored("\nAbort processus\n", "red", attrs=["blink", "bold"]))
