#ifndef LOGINDTO_
#define LOGINDTO_

#include <string>
#include "Network/Helper/json.hpp"
#include "Dto/Security/BaseSecurityDto.h"

namespace DTO::Security
{
using std::string;
using json = nlohmann::json;

    class LoginDto: public BaseSecurityDto
    {
        public:
            LoginDto(string Username, string Password);
            LoginDto() = default;
            ~LoginDto() override = default;

            string GetPassword() { return m_Password; }
            void SetPassword(string val) { m_Password = val; }

            void FromJson(const json& jsonObject) override;
            json ToJson(bool toSubmit) override;
        private:
            string m_Password;
    };
}

#endif // LOGINDTO_
