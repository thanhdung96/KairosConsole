#include "Dto/Security/BaseSecurityDto.h"
using namespace DTO::Security;

BaseSecurityDto::BaseSecurityDto(string Username)
{
    m_Username = Username;
}

BaseSecurityDto::~BaseSecurityDto()
{
    //dtor
}
