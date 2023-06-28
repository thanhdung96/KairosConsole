#include "Dto/App/StatusDto.h"

namespace DTO::App {
    bool StatusDto::Active() const
    {
        return m_Active;
    }

    void StatusDto::setActive(bool newActive)
    {
        m_Active = newActive;
    }

    void StatusDto::FromJson(const json &jsonObject)
    {

    }

    json StatusDto::ToJson(bool toSubmit)
    {
        json jsonObject;
        jsonObject["active"] = m_Active;

        if(toSubmit) {
            json retJson;
            retJson["data"] = jsonObject;
            return retJson;
        }

        return jsonObject;
    }
}
