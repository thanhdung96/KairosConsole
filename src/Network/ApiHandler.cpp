#include "Network/ApiHandler.h"
using namespace Network;

ApiHandler::ApiHandler() {
    m_UriBuilder.setScheme(Constants::HTTPS_SCHEME);
    m_UriBuilder.setMIncludePortNumber(false);
    m_UriBuilder.setMIncludeLastSlash(false);
    m_NwManager = new QNetworkAccessManager(this);
    connect(m_NwManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(finishedSlot(QNetworkReply*)));
}

ApiHandler::~ApiHandler()
{
    m_NwManager->deleteLater();
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

void ApiHandler::Execute(RequestMethod requestMethod) {
    this->buildPath();
    QNetworkRequest request = BaseRequest::getBaseNetworkRequest(m_UriBuilder.toString());
    QByteArray postData = QByteArray::fromStdString(m_requestBody);

    switch (requestMethod) {
        case RequestMethod::POST:
            m_NwManager->post(request, postData);
            break;
        default:
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

void ApiHandler::finishedSlot(QNetworkReply* reply)
{
    emit requestFinished(BaseResponse(
            reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt(),
            QString(reply->readAll()).toStdString()
        )
    );
    reply->deleteLater();
}
