#include "Network/ApiHandler.h"
using namespace Network;

ApiHandler::ApiHandler() {
    m_UriBuilder.setScheme(Constants::HTTPS_SCHEME);
    m_UriBuilder.setMIncludePortNumber(false);
    m_UriBuilder.setMIncludeLastSlash(false);
    curl_easy_setopt(m_CurlHandler.get(), CURLOPT_HTTPHEADER, m_Header.getHeader().get());
}

const string &ApiHandler::getMDomain() const {
    return m_Domain;
}

void ApiHandler::setMDomain(const string &mDomain) {
    m_UriBuilder.setHost(mDomain);
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

 const BaseResponse ApiHandler::Execute(RequestMethod requestMethod) {
    if(!m_CurlHandler) {
        throw runtime_error("Failed to initialize Curl");
    }

    string responseData;

    this->buildPath();
    string url = this->m_UriBuilder.toString();
    curl_easy_setopt(
        m_CurlHandler.get(),
        CURLOPT_URL,
        url.c_str()
    );

    curl_easy_setopt(m_CurlHandler.get(), CURLOPT_WRITEFUNCTION, &WriteResponse);
    curl_easy_setopt(m_CurlHandler.get(), CURLOPT_WRITEDATA, &responseData);

    switch (requestMethod) {
        case RequestMethod::POST:
            curl_easy_setopt(m_CurlHandler.get(), CURLOPT_POSTFIELDS, m_requestBody.c_str());
            break;
        case RequestMethod::PATCH:
            break;
        case RequestMethod::DELETE:
            break;
        case RequestMethod::GET:
            break;
    }

    curl_easy_perform(m_CurlHandler.get());
    long httpResponseCode;
    curl_easy_getinfo(m_CurlHandler.get(), CURLINFO_RESPONSE_CODE, &httpResponseCode);

    BaseResponse response;
    response.setResponseCode(httpResponseCode);
    response.setResponseData(responseData);

    return response;
}

void ApiHandler::buildPath() {
    m_UriBuilder.clearPath();
    m_UriBuilder.pushPath(m_Role);
    m_UriBuilder.pushPath(m_Model);
    m_UriBuilder.pushPath(m_Action);
    m_UriBuilder.pushPath(m_EntityId);
}

void ApiHandler::buildQuery() {
    m_UriBuilder.clearQuery();
}

size_t ApiHandler::WriteResponse(void *ptr, size_t size, size_t nmemb, void *userdata) {
    size_t real_size = size * nmemb;
    string* response = static_cast<std::string*>(userdata);
    response->append(static_cast<char*>(ptr), real_size);
    return real_size;
}
