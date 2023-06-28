#ifndef KAIROSCONSOLE_HTTPHEADER_H
#define KAIROSCONSOLE_HTTPHEADER_H

#include <string>
#include <QNetworkRequest>

namespace Network::Helper {
using std::string;

    class BaseRequest {
        public:
            static const QNetworkRequest getBaseNetworkRequest(const string& url);
            BaseRequest(const string& url);

        protected:
            BaseRequest() = default;
            ~BaseRequest() = default;

        private:
            inline static const string JSON = "application/json";
            inline static const string FORM_DATA = "multipart/form-data";
            inline static const string CONNECTION_KEEP_ALIVE = "keep-alive";
            inline static const string ACCEPT_ENCODING = "gzip, deflate, br";
            inline static const string USER_AGENT = "KairosConsole/0.0 Qt linux dev version";
    };
}
#endif //KAIROSCONSOLE_HTTPHEADER_H
