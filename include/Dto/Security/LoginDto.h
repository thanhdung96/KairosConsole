#ifndef LOGINDTO_
#define LOGINDTO_

#include <string>
#include "Network/Json/json.hpp"
#include "Dto/Security/BaseSecurityDto.h"

namespace DTO::Security
{
    using namespace std;
    using json = nlohmann::json;

    class LoginDto: public BaseSecurityDto
    {
        public:
            LoginDto(string Username, string Password);
            LoginDto();
            ~LoginDto() override = default;

            string GetPassword() { return m_Password; }
            void SetPassword(string val) { m_Password = val; }

            void FromJson(const json& jsonObject) override;
            json ToJson() override;
        private:
            string m_Password;
    };
}

#endif // LOGINDTO_
