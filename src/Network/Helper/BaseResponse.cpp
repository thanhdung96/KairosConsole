#include "Network/Helper/BaseResponse.h"
using namespace Network::Helper;

BaseResponse::BaseResponse()
{
    m_ResponseCode = Status::HTTP_OK;
}

BaseResponse::BaseResponse(long responseCode, const string& responseData)
{
    this->setResponseCode(responseCode);
    this->setResponseData(responseData);
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

const json& BaseResponse::getResponseData(){
    return m_ParsedResponseData;
}

string BaseResponse::GetRawResponse() const
{
    return m_RawResponseData;
}

BaseResponse BaseResponse::operator=(const BaseResponse &otherBaseReponse)
{
    return BaseResponse(otherBaseReponse.ResponseCode(), otherBaseReponse.GetRawResponse());
}
