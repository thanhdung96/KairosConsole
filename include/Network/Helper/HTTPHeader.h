#ifndef KAIROSCONSOLE_HTTPHEADER_H
#define KAIROSCONSOLE_HTTPHEADER_H

#include <string>
#include <memory>
#include <curl/curl.h>

namespace Network::Helper {
    using namespace std;
    typedef shared_ptr<struct curl_slist> SPHeader;

    class Header {
        public:
            Header();
            ~Header() = default;

            SPHeader getHeader();
            const string& getJwtToken();
            void setJwtToken(const string& token);

        protected:

        private:
            SPHeader m_LstHeaders;
            string m_JwtToken;

            const string ACCEPT_JSON = "Accept: application/json";
            const string AUTHORISATION = "Authorization: $token";
            const string CONNECTION_KEEP_ALIVE = "Connection: keep-alive";
            const string ACCEPT_ENCODING = "Accept-Encoding: gzip, deflate, br";
            const string USER_AGENT = "User-Agent: KairosConsole/0.0 libCurl linux dev version";
    };
}
#endif //KAIROSCONSOLE_HTTPHEADER_H
