#ifndef CHANGEPASSWORDDTO_H
#define CHANGEPASSWORDDTO_H

#include <BaseSecurityDto.h>
#include <string>

namespace DTO
{
    namespace Security
    {
        using namespace std;
        class ChangePasswordDto : public BaseSecurityDto
        {
            public:
                ChangePasswordDto();
                ChangePasswordDto(string Username, string OldPassword, string NewPassword);
                virtual ~ChangePasswordDto() override;

                string GetOldPassword() { return m_OldPassword; }
                void SetOldPassword(string val) { m_OldPassword = val; }
                string GetNewPassword() { return m_NewPassword; }
                void SetNewPassword(string val) { m_NewPassword = val; }

            protected:

            private:
                string m_OldPassword;
                string m_NewPassword;
        };
    }
}


#endif // CHANGEPASSWORDDTO_H
