
#include "httpwebserver.h"
#include <sbu2webapp/SBU2HTTPServer.h>
#include <map>
#include <iostream>
#include <string>

using namespace std;

int main(int argc, char** argv) {
    if (argc != 3) {
        cout << "Usage: " << argv[0] << " <jsonfilepath> <yamlfilepath>" << endl;
        return 1;
    }
    string jsonFilePath(argv[1]);
    string yamlFilePath(argv[2]);
    YamlConfig config(yamlFilePath);
    HttpWebserver *httpServer = new HttpWebserver(jsonFilePath, yamlFilePath);
    map<string, SBU2WebService*> *webServices = new map<string , SBU2WebService*>;
    string endUrl = config["httpServer"]["endUrl"];
    webServices->insert(make_pair(endUrl,httpServer));
    string loadbalancer = config["httpServer"]["load"];
    int loadBalancer = stoi(loadbalancer);
    SBU2LoadBalancer *loadBalancerObj = new SBU2LoadBalancer(loadBalancer,webServices);
    string serverPort = config["httpServer"]["port"];
    int port = stoi(serverPort);

    SBU2HTTPServer *httpServerObj = new SBU2HTTPServer(port, loadBalancerObj);
    cout << "Connecting..." << endl;

    httpServerObj->run();
    while(1);
}

