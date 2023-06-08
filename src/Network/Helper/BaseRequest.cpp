#include "Network/Helper/BaseRequest.h"
using namespace Network::Helper;

QNetworkRequest BaseRequest::getBaseNetworkRequest(const string &url)
{
    QNetworkRequest request;
    request.setUrl(QUrl(QString::fromStdString(url)));
    request.setHeader(QNetworkRequest::KnownHeaders::ContentTypeHeader, &BaseRequest::JSON);
    request.setHeader(QNetworkRequest::KnownHeaders::UserAgentHeader, &BaseRequest::USER_AGENT);

    if(!Session::getJwtToken().empty()) {
        request.setRawHeader("Authorization", QByteArray::fromStdString(Session::getJwtToken()));
    }

    return request;
}
