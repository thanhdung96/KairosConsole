#include "Dto/Security/ChangePasswordDto.h"
using namespace DTO::Security;

ChangePasswordDto::ChangePasswordDto(string Username, string OldPassword, string NewPassword): BaseSecurityDto(Username)
{
    m_OldPassword = OldPassword;
    m_NewPassword = NewPassword;
}

ChangePasswordDto::ChangePasswordDto(): BaseSecurityDto("")
{
    m_OldPassword = "";
    m_NewPassword = "";
}

ChangePasswordDto::~ChangePasswordDto()
{
    //dtor
}
