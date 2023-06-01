#include "ActivateDto.h"
using namespace DTO::Security;

ActivateDto::ActivateDto(): BaseSecurityDto("")
{
    m_Hashcode = "";
}

ActivateDto::ActivateDto(string Username, string Hashcode): BaseSecurityDto(Username)
{
    m_Hashcode = Hashcode;
}

ActivateDto::~ActivateDto()
{
    //dtor
}
