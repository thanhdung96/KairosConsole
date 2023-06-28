#ifndef KAIROSCONSOLE_APIHANDLER_H
#define KAIROSCONSOLE_APIHANDLER_H

#include "Helper/UriBuilder.h"
#include <string>
#include <vector>
#include <QNetworkReply>
#include <QNetworkAccessManager>

namespace Network {
using std::string;

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
            ~ApiHandler() = default;

            void Execute(RequestMethod requestMethod, string receiverSlot);

            const string &getMDomain() const;
            void setMDomain(const string &mDomain);
            const string &getRequestBody() const;
            void setRequestBody(const string &requestBody);
            const string &getMModel() const;
            void setMModel(const string &Model);
            const string &getMAction() const;
            void setMAction(const string &Action);
            const string &getMEntityId() const;
            void setMEntityId(const string &EntityId);
            void pushQuery(const string& query);
            void clearQuery();

        private:
            Network::Helper::UriBuilder m_UriBuilder;
            string m_Domain;
            string m_Model;
            string m_Action;
            string m_EntityId;
            string m_requestBody;
            QNetworkAccessManager m_NwManager;
            string m_LastReceiverSlot;

        private:
            void buildPath(bool includeRole);
    };
}
#endif //KAIROSCONSOLE_APIHANDLER_H
