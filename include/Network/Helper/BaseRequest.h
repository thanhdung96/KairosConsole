#ifndef KAIROSCONSOLE_HTTPHEADER_H
#define KAIROSCONSOLE_HTTPHEADER_H

#include <string>
#include <QNetworkRequest>
#include "App/Session.h"

namespace Network::Helper {
    using namespace std;
    using namespace App;

    class BaseRequest {
        public:
            static QNetworkRequest getBaseNetworkRequest(const string& url);

        protected:
            BaseRequest() = default;
            ~BaseRequest() = default;

        private:
            static string m_JwtToken;
            const string JSON = "application/json";
            const string FORM_DATA = "multipart/form-data";
            const string CONNECTION_KEEP_ALIVE = "keep-alive";
            const string ACCEPT_ENCODING = "gzip, deflate, br";
            const string USER_AGENT = "KairosConsole/0.0 Qt linux dev version";
    };
}
#endif //KAIROSCONSOLE_HTTPHEADER_H
