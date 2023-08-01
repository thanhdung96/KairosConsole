#include "Dto/Management/AvailableTypeDto.h"

namespace DTO::Management {
    string AvailableTypeDto::getId() const
    {
        return m_Id;
    }

    void AvailableTypeDto::setId(const string &newId)
    {
        m_Id = newId;
    }

    string AvailableTypeDto::getName() const
    {
        return m_Name;
    }

    void AvailableTypeDto::setName(const string &newName)
    {
        m_Name = newName;
    }

    string AvailableTypeDto::getDescription() const
    {
        return m_Description;
    }

    void AvailableTypeDto::setDescription(const string &newDescription)
    {
        m_Description = newDescription;
    }

    double AvailableTypeDto::getMaximumDay() const
    {
        return m_MaximumDay;
    }

    void AvailableTypeDto::setMaximumDay(double newMaximumDay)
    {
        m_MaximumDay = newMaximumDay;
    }

    bool AvailableTypeDto::isLeaveToll() const
    {
        return m_LeaveToll;
    }

    void AvailableTypeDto::setLeaveToll(bool newLeaveToll)
    {
        m_LeaveToll = newLeaveToll;
    }

    bool AvailableTypeDto::isRequireFile() const
    {
        return m_RequireFile;
    }

    void AvailableTypeDto::setRequireFile(bool newRequireFile)
    {
        m_RequireFile = newRequireFile;
    }

    bool AvailableTypeDto::isUnpaid() const
    {
        return m_Unpaid;
    }

    void AvailableTypeDto::setUnpaid(bool newUnpaid)
    {
        m_Unpaid = newUnpaid;
    }

    string AvailableTypeDto::getDescriptionRequiredFiles() const
    {
        return m_DescriptionRequiredFiles;
    }

    void AvailableTypeDto::setDescriptionRequiredFiles(const string &newDescriptionRequiredFiles)
    {
        m_DescriptionRequiredFiles = newDescriptionRequiredFiles;
    }

    bool AvailableTypeDto::isActive() const
    {
        return m_Active;
    }

    void AvailableTypeDto::setActive(bool newActive)
    {
        m_Active = newActive;
    }

    void AvailableTypeDto::FromJson(const json &jsonObject)
    {
        m_Id = jsonObject["id"];
        m_Name = jsonObject["name"];
        if(jsonObject.contains("description")) {
            m_Description = jsonObject["description"];
        }
        m_MaximumDay = jsonObject["maximumDay"];
        m_LeaveToll = jsonObject["leaveToll"];
        m_RequireFile = jsonObject["requireFile"];
        m_Unpaid = jsonObject["unpaid"];
        if(jsonObject.contains("descriptionRequiredFiles")) {
            m_DescriptionRequiredFiles = jsonObject["descriptionRequiredFiles"];
        }
        m_Active = jsonObject["active"];
    }

    json AvailableTypeDto::ToJson(bool toSubmit)
    {
        json jsonObject;
        jsonObject["name"] = m_Name;
        jsonObject["description"] = m_Description;
        jsonObject["maximumDay"] = m_MaximumDay;
        jsonObject["leaveToll"] = m_LeaveToll;
        jsonObject["requireFile"] = m_RequireFile;
        jsonObject["unpaid"] = m_Unpaid;
        jsonObject["descriptionRequiredFiles"] = m_DescriptionRequiredFiles;
        jsonObject["active"] = m_Active;

        if(toSubmit) {
            json retJson;
            retJson["data"] = jsonObject;
            return retJson;
        }
        return jsonObject;
    }
}
