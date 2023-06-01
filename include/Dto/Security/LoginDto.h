#ifndef LOGINDTO_
#define LOGINDTO_

#include <string>
#include "BaseSecurityDto.h"

namespace DTO
{
    namespace Security
    {
        using namespace std;
        class LoginDto: public BaseSecurityDto
        {
            public:
                LoginDto(string Username, string Password);
                LoginDto();
                virtual ~LoginDto() override;

                string GetPassword() { return m_Password; }
                void SetPassword(string val) { m_Password = val; }

            private:
                string m_Password;
        };
    }
}

#endif // LOGINDTO_
