#ifndef BASESECURITYDTO_H
#define BASESECURITYDTO_H

#include <string>
#include "Network/Json/json.hpp"
#include "Dto/BaseDto.h"

namespace DTO::Security
{
    using namespace std;
    using json = nlohmann::json;

    class BaseSecurityDto: BaseDto
    {
        public:
            explicit BaseSecurityDto(string Username);
            virtual ~BaseSecurityDto();

            string GetUsername() { return m_Username; }
            void SetUsername(string val) { m_Username = val; }

            void FromJson(const json& jsonObject) override;
            json ToJson() override;
        protected:
            string m_Username;
    };
}
#endif // BASESECURITYDTO_H
