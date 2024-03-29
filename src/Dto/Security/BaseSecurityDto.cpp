#include "Dto/Security/BaseSecurityDto.h"

namespace DTO::Security {
    BaseSecurityDto::BaseSecurityDto(string Username)
    {
        m_Username = Username;
    }

    void BaseSecurityDto::FromJson(const json &jsonObject) {
        m_Username = jsonObject["username"];
    }

    json BaseSecurityDto::ToJson(bool toSubmit) {
        json jsonObject;
        jsonObject["username"] = m_Username;

        return jsonObject;
    }
}
