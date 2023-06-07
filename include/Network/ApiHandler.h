#ifndef KAIROSCONSOLE_APIHANDLER_H
#define KAIROSCONSOLE_APIHANDLER_H

#include <curl/curl.h>
#include <string>
#include <sstream>
#include <memory>
#include <stdexcept>
#include "Constants/ApiConstants.h"
#include "Helper/UriBuilder.h"
#include "Helper/HTTPHeader.h"
#include "Response/BaseResponse.h"

namespace Network {
    using namespace std;
    using namespace Network::Helper;
    using namespace DataResponse;
    typedef unique_ptr<CURL, decltype(&curl_easy_cleanup)> UPtrCurl;

    class ApiHandler {
        public:
            enum class RequestMethod {
                GET,
                POST,
                PATCH,
                DELETE
            };

            ApiHandler();
            ~ApiHandler() = default;

            const BaseResponse Execute(RequestMethod requestMethod);

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
            UPtrCurl m_CurlHandler = UPtrCurl(curl_easy_init(), curl_easy_cleanup);

            UriBuilder m_UriBuilder;
            Header m_Header;
            string m_Domain;
            string m_Role;
            string m_Model;
            string m_Action;
            string m_EntityId;
            string m_requestBody;

        private:
            static size_t WriteResponse(void* ptr, size_t size, size_t nmemb, void* userdata);

            void buildPath();
            void buildQuery();
    };
}
#endif //KAIROSCONSOLE_APIHANDLER_H
