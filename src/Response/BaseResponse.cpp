#include "Response/BaseResponse.h"
using namespace DataResponse;

BaseResponse::BaseResponse()
{
    m_ResponseCode = Status::HTTP_OK;
}

BaseResponse::~BaseResponse()
{
    //dtor
}

long BaseResponse::ResponseCode() const
{
    return m_ResponseCode;
}

void BaseResponse::setResponseCode(long newResponseCode)
{
    m_ResponseCode = newResponseCode;
}

void BaseResponse::setResponseData(const string &newResponseData)
{
    m_RawResponseData = newResponseData;
    m_ParsedResponseData = json::parse(newResponseData);
}

string BaseResponse::ResponseData(const string field) const
{
    string data = m_ParsedResponseData[field];
    return data.empty() ? "" : data;
}

string BaseResponse::GetRawResponse() const
{
    return m_RawResponseData;
}

BaseResponse BaseResponse::operator=(const BaseResponse &otherBaseReponse)
{
    BaseResponse newBaseResponse;
    newBaseResponse.setResponseCode(otherBaseReponse.ResponseCode());
    newBaseResponse.setResponseData(otherBaseReponse.GetRawResponse());

    return newBaseResponse;
}
