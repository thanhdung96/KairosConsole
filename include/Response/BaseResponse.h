#ifndef BASERESPONSE_
#define BASERESPONSE_

#include <string>

namespace DataResponse
{
    using namespace std;
    class BaseResponse
    {
        public:
            virtual ~BaseResponse();

            // successful codes
            const static int HTTP_OK = 200;
            const static int HTTP_CREATED = 201;
            // client error codes
            const static int HTTP_BAD_REQUEST = 400;
            const static int HTTP_UNAUTHORIZED = 401;
            const static int HTTP_FORBIDDEN = 403;
            const static int HTTP_NOT_FOUND = 404;
            const static int HTTP_GONE = 410;
            // server error codes
            const static int HTTP_INTERNAL_SERVER_ERROR = 500;

        protected:
            BaseResponse(string ResponseData, int ResponseCode);
            BaseResponse();

        private:
            string m_ResponseData;
            int m_ResponseCode;
    };
}
#endif // BASERESPONSE_
