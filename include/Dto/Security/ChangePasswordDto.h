#ifndef CHANGEPASSWORDDTO_H
#define CHANGEPASSWORDDTO_H

#include "Dto/Security/BaseSecurityDto.h"
#include <string>

namespace DTO::Security
{
using std::string;

class ChangePasswordDto : public BaseSecurityDto
    {
        public:
            ChangePasswordDto();
            ChangePasswordDto(string Username, string OldPassword, string NewPassword);
            ~ChangePasswordDto() = default;

            const string& getOldPassword();
            void setOldPassword(const string &newOldPassword);
            const string& getNewPassword();
            void setNewPassword(const string &newNewPassword);

            void FromJson(const json& jsonObject) override;
            json ToJson(bool toSubmit) override;

        private:
            string m_OldPassword;
            string m_NewPassword;
    };
}
#endif // CHANGEPASSWORDDTO_H
