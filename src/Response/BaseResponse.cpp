#include "Response/BaseResponse.h"
using namespace DataResponse;

BaseResponse::BaseResponse(string ResponseData, int ResponseCode)
{
    m_ResponseData = ResponseData;
    m_ResponseCode = ResponseCode;
}

BaseResponse::BaseResponse()
{
    m_ResponseData = "";
    m_ResponseCode = BaseResponse::HTTP_OK;
}

BaseResponse::~BaseResponse()
{
    //dtor
}
