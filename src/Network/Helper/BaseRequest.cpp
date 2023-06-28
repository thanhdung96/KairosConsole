#include "Network/Helper/BaseRequest.h"
#include "App/Session.h"
#include <QString>
#include <QByteArray>

namespace Network::Helper {
    using namespace App;

    const QNetworkRequest BaseRequest::getBaseNetworkRequest(const string &url)
    {
        QNetworkRequest request;
        request.setUrl(QUrl(QString::fromStdString(url)));
        request.setRawHeader("User-Agent", QByteArray::fromStdString(BaseRequest::USER_AGENT));
        request.setRawHeader("Content-Type", QByteArray::fromStdString(BaseRequest::JSON));

        if(!Session::getJwtToken().empty()) {
            request.setRawHeader("Authorization", QByteArray::fromStdString(Session::getJwtToken()));
        }

        return request;
    }
}
