#include "httpwebserver.h"
#include <ubacyaml/YamlConfig.h>

HttpWebserver::HttpWebserver(const string &jsonFilePath,const string &yamlFilePath):SBU2WebService() {
    // Extract JSON file path from the configuration
    jsonlibrary = new JsonLibrary(jsonFilePath);
    jsonlibrary->readJsonFile();   
    this->yamlFilePath = yamlFilePath;
}

HttpWebserver::~HttpWebserver() {
     delete jsonlibrary;
}

void HttpWebserver::onInvalidJSONRequest(HTTPServerRequest *request, HTTPConnection *connection, string &rawRequest) {
    cerr << "Request recevied : " << rawRequest << endl;
    string infoid,infomsg;
    YamlConfig config(yamlFilePath);
    infoid = config["Response_onInvalidJson"]["infoid"];
    infomsg = config["Response_onInvalidJson"]["infomsg"];
    MSFRequest* msfRequest = new MSFRequest(rawRequest);
    MSFResponse* errorResponse = new MSFResponse(msfRequest);
    string errorMessage = "Invalid JSON request: " + rawRequest;
    errorResponse->addToData("error", errorMessage);

    errorResponse->setInfoID(infoid);
    errorResponse->setInfoMsg(infomsg);
    errorResponse->setSvcName(config["Response_onInvalidJson"]["svcName"]);
    errorResponse->setSvcGroup(config["Response_onInvalidJson"]["svcGroup"]);
    sendResponse(errorResponse, connection);
    connection->release();
}

void HttpWebserver::onPostProcessRequest(MSFRequest* msfRequest, MSFResponse* msfResponse, HTTPConnection* connection) {
    // Reading request data
    cout << "Request received" << endl;
    string request = msfRequest->toString();
    YamlConfig config(this->yamlFilePath);
    JsonParser parser(request);
    requestObject = parser.getJsonObject();

    if (requestObject.hasKey(config["Response_onPostProcessRequest"]["key"])) {
        string contentValue = requestObject[config["Response_onPostProcessRequest"]["key"]];

        if(contentValue == config["Response_onPostProcessRequest"]["value1"]){
            requestObject = jsonlibrary->getJsonObjectList();
            msfResponse->addToData("LangList", requestObject);
            cout << "Language list: "<< requestObject.toString() << endl;
        } else if (contentValue == config["Response_onPostProcessRequest"]["value2"]) {
            requestObject = jsonlibrary->getJsonObjectUrl();
            msfResponse->addToData("LangUrl", requestObject);
            cout << requestObject.toString() << endl;
        } else {
            cerr << "Invalid content value." << endl;
	    string infoid = config["Response_onPostProcessRequest"]["infoid"];
	    string infomsg = config["Response_onPostProcessRequest"]["infomsg"];

            msfResponse->setInfoID(infoid);
            msfResponse->setInfoMsg(infomsg);
        }
    } 
    msfResponse->setSvcName(config["Response_onPostProcessRequest"]["svcName"]);
    msfResponse->setSvcGroup(config["Response_onPostProcessRequest"]["svcGroup"]);
    cout << msfResponse->toString() << endl;
    // Send the response
    sendResponse(msfResponse, connection);
    connection->release();
}

