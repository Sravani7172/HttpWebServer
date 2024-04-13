#ifndef HTTP_WEBSERVER_H
#define HTTP_WEBSERVER_H

#include <iostream>
#include <string>
#include <sbu2webapp/SBU2WebService.h>
#include <sbu2webapp/SBU2HTTPServer.h>
#include <jsonlibrary/json_library.h>
#include <map>
#include <ubacyaml/YamlConfig.h> // Include YAML library

using namespace std;
using namespace SBU2;

class HttpWebserver : public SBU2WebService {
public:
    HttpWebserver(const string &jsonFilePath,const string &yamlFilePath);
    ~HttpWebserver();
    void onInvalidJSONRequest(HTTPServerRequest *request, HTTPConnection *connection, string &rawRequest);
    void onPostProcessRequest(MSFRequest *msfRequest, MSFResponse *msfResponse, HTTPConnection *connection);

private:
    JsonLibrary *jsonlibrary;
    string jsonFilePath, yamlFilePath;
    JsonObject requestObject, responseObject;
};

#endif

