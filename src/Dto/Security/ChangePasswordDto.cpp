#include "Dto/Security/ChangePasswordDto.h"

namespace DTO::Security {
    ChangePasswordDto::ChangePasswordDto(string Username, string OldPassword, string NewPassword): BaseSecurityDto(Username)
    {
        m_OldPassword = OldPassword;
        m_NewPassword = NewPassword;
    }

    void ChangePasswordDto::FromJson(const json &jsonObject)
    {
        m_NewPassword = jsonObject["newPassword"];
        m_OldPassword = jsonObject["oldPassword"];
    }

    json ChangePasswordDto::ToJson(bool toSubmit)
    {
        json jsonObject;
        jsonObject["newPassword"] = m_NewPassword;
        jsonObject["oldPassword"] = m_OldPassword;

        return jsonObject;
    }

    const string& ChangePasswordDto::getOldPassword()
    {
        return m_OldPassword;
    }

    void ChangePasswordDto::setOldPassword(const string &newOldPassword)
    {
        m_OldPassword = newOldPassword;
    }

    const string& ChangePasswordDto::getNewPassword()
    {
        return m_NewPassword;
    }

    void ChangePasswordDto::setNewPassword(const string &newNewPassword)
    {
        m_NewPassword = newNewPassword;
    }

    ChangePasswordDto::ChangePasswordDto(): BaseSecurityDto("")
    {
        m_OldPassword = "";
        m_NewPassword = "";
    }
}
