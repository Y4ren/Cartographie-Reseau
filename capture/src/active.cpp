#include "active.hpp"

#ifdef __unix__
#include <jsoncpp/json/json.h>
#elif defined __APPLE__
#include <json/json.h> // <json/json.h> for macOS
#endif

void Active::startActiveDetection()
{
    int pid = fork();

    if (!pid)
    {
        string command = "python3";
        string argument = "./Active/activeDetection.py";
        char *argument_list[] = {const_cast<char *>(command.c_str()), const_cast<char *>(argument.c_str()), NULL};
        execvp(argument_list[0], argument_list);
        return;
    }

    wait(NULL);

    Json::Value root;
    Json::Reader reader;

    std::ifstream file("./machine.json");
    bool parsed = reader.parse(file, root, false);
    if (!parsed)
    {
        std::cout << "Failed to parse JSON" << std::endl;
        return;
    }

    // Access the hosts field
    Json::Value hosts = root["hosts"];

    // Iterate over the hosts array
    for (const auto &host : hosts)
    {
        Node *node = Manager::getNode(host["MAC"][0].asString());
        node->addIPv4(host["IPV4"].asString());
        node->addIPv4(host["IPV6"].asString());
        node->addDistance(host["distance"][0].asInt());
        node->addBootInformation(host["lastBoot"][0].asString(), host["uptime"][0].asInt());
        // Get the osMatch array
        Json::Value osMatch = host["osMatch"];

        // Iterate over the osMatch array
        for (const auto &os : osMatch)
        {
            node->addOS(os.asString());
        }

        // Get the services array
        Json::Value services = host["services"];

        // Iterate over the services array
        for (const auto &service : services)
        {
            string name, banner, state;
            int port;
            vector<string> cpes = {};

            // Iterate over the serviceName array
            for (const auto &_name : service["serviceName"])
            {
                name = _name.asString();
            }
            // Iterate over the banner array
            for (const auto &_banner : service["banner"])
            {
                banner = _banner.asString();
            }
            // // Iterate over the cpeList array
            // for (const auto &cpe : service["cpeList"])
            // {
            //     cpes.push_back(cpe.asString());
            // }

            // Iterate over the port array
            for (const auto &_port : service["port"])
            {
                port = _port.asInt();
            }
            // Iterate over the state array
            for (const auto &_state : service["state"])
            {
                state = _state.asString();
            }

            node->addService(new OpenService(name, port, banner, state, cpes));
        }
    }
}
