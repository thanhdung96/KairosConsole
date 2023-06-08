#include "App/Session.h"
using namespace App;

const string& Session::getJwtToken()
{
    return m_JwtToken;
}

void Session::setJwtToken(const string &newJwtToken)
{
    m_JwtToken = newJwtToken;
}
