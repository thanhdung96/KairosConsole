#include "Network/Helper/HTTPHeader.h"
using namespace Network::Helper;

Header::Header() {
    //appending headers
    struct curl_slist* list = nullptr;
    list = curl_slist_append(list,Header::ACCEPT_JSON.c_str());
    list = curl_slist_append(list,Header::CONNECTION_KEEP_ALIVE.c_str());
    list = curl_slist_append(list, Header::USER_AGENT.c_str());
    list = curl_slist_append(list, Header::ACCEPT_ENCODING.c_str());

    if(!m_JwtToken.empty()) {
        string jwtHeader = Header::AUTHORISATION;
        curl_slist_append(
            m_LstHeaders.get(),
            jwtHeader.replace(
                    Header::USER_AGENT.find("$token"),
                    6,
                    m_JwtToken
                ).c_str()
        );
    }

    m_LstHeaders = SPHeader(list, curl_slist_free_all);
    list = nullptr;
}

SPHeader Header::getHeader() {
    return m_LstHeaders;
}

const string &Header::getJwtToken() {
    return m_JwtToken;
}

void Header::setJwtToken(const string &token) {
    m_JwtToken = token;
}
