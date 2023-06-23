#include "Dto/Management/RoleDto.h"

namespace DTO::Management {
    string RoleDto::getId() const
    {
        return m_Id;
    }

    void RoleDto::setId(const string &newId)
    {
        m_Id = newId;
    }

    string RoleDto::getName() const
    {
        return m_Name;
    }

    void RoleDto::setName(const string &newName)
    {
        m_Name = newName;
    }

    string RoleDto::getDescription() const
    {
        return m_Description;
    }

    void RoleDto::setDescription(const string &newDescription)
    {
        m_Description = newDescription;
    }

    int RoleDto::getMaxLeaveBalance() const
    {
        return m_MaxLeaveBalance;
    }

    void RoleDto::setMaxLeaveBalance(int newMaxLeaveBalance)
    {
        m_MaxLeaveBalance = newMaxLeaveBalance;
    }

    bool RoleDto::isActive() const
    {
        return m_Active;
    }

    void RoleDto::setActive(bool newActive)
    {
        m_Active = newActive;
    }

    string RoleDto::getCode() const
    {
        return m_Code;
    }

    void RoleDto::setCode(const string &newCode)
    {
        m_Code = newCode;
    }

    void RoleDto::FromJson(const json &jsonObject)
    {
        m_Id = jsonObject["id"];
        m_Name = jsonObject["name"];
        m_Description = jsonObject["description"];
        m_Active = jsonObject["active"];
        m_Code = jsonObject["code"];
        m_MaxLeaveBalance = jsonObject["maxLeaveBalance"];
    }

    json RoleDto::ToJson(bool toSubmit)
    {
        json jsonObject;
        if(!m_Id.empty()) {
            jsonObject["id"] = m_Id;
        }
        jsonObject["name"] = m_Name;
        jsonObject["description"] = m_Description;
        jsonObject["active"] = m_Active;
        jsonObject["code"] = m_Code;
        jsonObject["maxLeaveBalance"] = m_MaxLeaveBalance;

        if(toSubmit) {
            json retJson;
            retJson["data"] = jsonObject;
            return retJson;
        }
        return jsonObject;
    }
}
