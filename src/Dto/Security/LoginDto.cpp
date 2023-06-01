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

LoginDto::~LoginDto()
{
    //dtor
}
