#ifndef BASERESPONSE_
#define BASERESPONSE_

#include <string>
#include "Network/Helper/json.hpp"

namespace Network::Helper
{
    using namespace std;
    using json = nlohmann::json;

    class BaseResponse
    {
        public:
            enum Status {
                HTTP_OK = 200,
                HTTP_CREATED = 201,
                HTTP_BAD_REQUEST = 400,
                HTTP_UNAUTHORIZED = 401,
                HTTP_FORBIDDEN = 403,
                HTTP_NOT_FOUND = 404,
                HTTP_GONE = 410,
                HTTP_INTERNAL_SERVER_ERROR = 500
            };
            BaseResponse();
            BaseResponse(long responseCode, const string &responseData);
            ~BaseResponse();

            long ResponseCode() const;
            void setResponseCode(long newResponseCode);
            void setResponseData(const string &newResponseData);
            string ResponseData(const string field) const;
            string GetRawResponse() const;
            BaseResponse operator=(const BaseResponse& otherBaseReponse);

    private:
            long m_ResponseCode;
            json m_ParsedResponseData;
            string m_RawResponseData;
    };
}
#endif // BASERESPONSE_
