#ifndef KAIROSCONSOLE_APIHANDLER_H
#define KAIROSCONSOLE_APIHANDLER_H

#include "Helper/UriBuilder.h"
#include "Helper/BaseRequest.h"
#include "Helper/BaseResponse.h"
#include "Network/Constants/ApiConstants.h"
#include <string>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>

namespace Network {
    using namespace std;
    using namespace Network::Helper;

    class ApiHandler: public QObject {
        Q_OBJECT

        public:
            enum class RequestMethod {
                GET,
                POST,
                PATCH,
                DELETE
            };

            ApiHandler();
            ~ApiHandler();

            void Execute(RequestMethod requestMethod);

            const string &getMDomain() const;
            void setMDomain(const string &mDomain);
            const string &getMRole() const;
            void setMRole(const string &mRole);
            const string &getRequestBody() const;
            void setRequestBody(const string &requestBody);
            const string &getMModel() const;
            void setMModel(const string &Model);
            const string &getMAction() const;
            void setMAction(const string &Action);
            const string &getMEntityId() const;
            void setMEntityId(const string &EntityId);

        signals:
            void requestFinished(BaseResponse);

        private:
            UriBuilder m_UriBuilder;
            string m_Domain;
            string m_Role;
            string m_Model;
            string m_Action;
            string m_EntityId;
            string m_requestBody;
            QNetworkAccessManager* m_NwManager;

        private:
            void buildPath();
            void buildQuery();

        private slots:
            void finishedSlot(QNetworkReply* reply);
    };
}
#endif //KAIROSCONSOLE_APIHANDLER_H
