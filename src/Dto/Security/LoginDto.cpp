#include "Dto/Security/LoginDto.h"
using namespace DTO::Security;

LoginDto::LoginDto(string Username, string Password): BaseSecurityDto(Username)
{
    m_Password = Password;
}

LoginDto::LoginDto(): BaseSecurityDto("")
{
    m_Password = "";
}

void LoginDto::FromJson(const json &jsonObject) {
    m_Username = jsonObject["username"];
    m_Password = jsonObject["password"];
}

json LoginDto::ToJson(bool toSubmit) {
    json jsonObject;
    jsonObject["username"] = m_Username;
    jsonObject["password"] = m_Password;

    return jsonObject;
}
