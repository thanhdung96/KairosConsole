#ifndef KAIROSCONSOLE_APIHANDLER_H
#define KAIROSCONSOLE_APIHANDLER_H

#include <curl/curl.h>
#include <string>
#include <sstream>
#include <memory>
#include <stdexcept>
#include "HTTPConstants.h"

namespace Network {
    using namespace std;
    class ApiHandler {
        public:
            ApiHandler() = default;
            ~ApiHandler() = default;

            string Execute(Constants::RequestMethod requestMethod);

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

        private:
            unique_ptr<CURL, decltype(&curl_easy_cleanup)> m_CurlHandler =
                    unique_ptr<CURL, decltype(&curl_easy_cleanup)>(curl_easy_init(), curl_easy_cleanup);

            string m_Domain;
            string m_Role;
            string m_Model;
            string m_Action;
            string m_EntityId;
            string m_requestBody;

        private:
            string constructUrl();
            static size_t WriteResponse(void* ptr, size_t size, size_t nmemb, void* userdata) {
                size_t real_size = size * nmemb;
                std::string* response = static_cast<std::string*>(userdata);
                response->append(static_cast<char*>(ptr), real_size);
                return real_size;
            }
    };
}
#endif //KAIROSCONSOLE_APIHANDLER_H
