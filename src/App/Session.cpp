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

const string& Session::getUsername()
{
    return m_Username;
}

void Session::setUsername(const string &newUsername)
{
    m_Username = newUsername;
}

const string& Session::getEmail()
{
    return m_Email;
}

void Session::setEmail(const string &newEmail)
{
    m_Email = newEmail;
}

string Session::getRole()
{
    return m_Role;
}

void Session::setRole(const string &newRole)
{
    m_Role = newRole;
}
