#include <iostream>
#include "Network/ApiHandler.h"
using namespace Network;

const string &ApiHandler::getMDomain() const {
    return m_Domain;
}

void ApiHandler::setMDomain(const string &mDomain) {
    m_Domain = mDomain;
}

const string &ApiHandler::getMRole() const {
    return m_Role;
}

void ApiHandler::setMRole(const string &mRole) {
    m_Role = mRole;
}

const string &ApiHandler::getRequestBody() const {
    return m_requestBody;
}

void ApiHandler::setRequestBody(const string &requestBody) {
    ApiHandler::m_requestBody = requestBody;
}

const string &ApiHandler::getMModel() const {
    return m_Model;
}

void ApiHandler::setMModel(const string &mModel) {
    m_Model = mModel;
}

const string &ApiHandler::getMAction() const {
    return m_Action;
}

void ApiHandler::setMAction(const string &mAction) {
    m_Action = mAction;
}

const string &ApiHandler::getMEntityId() const {
    return m_EntityId;
}

void ApiHandler::setMEntityId(const string &mEntityId) {
    m_EntityId = mEntityId;
}

string ApiHandler::constructUrl() {
    stringstream urlStream;

    urlStream << m_Domain;
    if(m_Domain[m_Domain.size() - 1] != '/'){
        urlStream << '/';
    }

    if(!m_Role.empty()){
        urlStream << m_Role;
        if(m_Role[m_Role.size() - 1] != '/'){
            urlStream << '/';
        }
    }

    urlStream << m_Model;
    if(m_Model[m_Model.size() - 1] != '/'){
        urlStream << '/';
    }

    urlStream << m_Action;
    if(m_Action[m_Action.size() - 1] != '/' && !m_EntityId.empty()){
        urlStream << '/';
    }

    if(!m_EntityId.empty()){
        urlStream << m_EntityId;
    }

    string url;
    urlStream >> url;
    return url;
}

string ApiHandler::Execute(Constants::RequestMethod requestMethod) {
    if(!m_CurlHandler) {
        throw runtime_error("Failed to initialize Curl");
    }

    string response;
    CURLcode res;

    std::cout << this->constructUrl().c_str();
    curl_easy_setopt(
        m_CurlHandler.get(),
        CURLOPT_URL,
        this->constructUrl().c_str()
    );

    curl_easy_setopt(m_CurlHandler.get(), CURLOPT_WRITEFUNCTION, &WriteResponse);
    curl_easy_setopt(m_CurlHandler.get(), CURLOPT_WRITEDATA, &response);

    switch (requestMethod) {
        case Constants::RequestMethod::POST:
            curl_easy_setopt(m_CurlHandler.get(), CURLOPT_POSTFIELDS, m_requestBody.c_str());
            break;
        case Constants::RequestMethod::PATCH:
            break;
        case Constants::RequestMethod::DELETE:
            break;
        case Constants::RequestMethod::GET:
            break;
    }

    res = curl_easy_perform(m_CurlHandler.get());

    if(res != CURLE_OK) {
        cout << "failed to perform: " << res << endl;
    }

    return response;
}
