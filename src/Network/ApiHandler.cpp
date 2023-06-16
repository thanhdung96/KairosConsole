#include "Network/ApiHandler.h"
#include <QNetworkRequest>
#include "Network/Helper/BaseRequest.h"
#include "Network/Constants/ApiConstants.h"
#include <exception>
using namespace Network;

ApiHandler::ApiHandler() {
    m_UriBuilder.setScheme(Constants::HTTPS_SCHEME);
    m_UriBuilder.setMIncludePortNumber(false);
    m_UriBuilder.setMIncludeLastSlash(false);
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

void ApiHandler::Execute(RequestMethod requestMethod, string receiverSlot) {
    this->buildPath();
    QNetworkRequest request = BaseRequest::getBaseNetworkRequest(m_UriBuilder.toString());
    QByteArray postData = QByteArray::fromStdString(m_requestBody);
    m_NwManager.setParent(this);

    if(!m_LastReceiverSlot.empty()) {
        disconnect(
            &m_NwManager,
            SIGNAL(finished(QNetworkReply*)),
            this->parent(),
            m_LastReceiverSlot.c_str()
        );
    }
    connect(
        &m_NwManager,
        SIGNAL(finished(QNetworkReply*)),
        this->parent(),
        receiverSlot.c_str()
    );
    m_LastReceiverSlot = receiverSlot;

    // default method is get
    switch (requestMethod) {
        case RequestMethod::POST:
            m_NwManager.post(request, postData);
            break;
        case RequestMethod::PATCH:
            m_NwManager.sendCustomRequest(request, "PATCH", postData);
            break;
        case RequestMethod::DELETE:
            throw std::exception();
            break;
        default:
            m_NwManager.get(request);
            break;
    }
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
