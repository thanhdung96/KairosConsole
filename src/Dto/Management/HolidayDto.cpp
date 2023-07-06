#include "Dto/Management/HolidayDto.h"

namespace DTO::Management {
    string HolidayDto::getId() const
    {
        return m_Id;
    }

    void HolidayDto::setId(const string &newId)
    {
        m_Id = newId;
    }

    string HolidayDto::getName() const
    {
        return m_Name;
    }

    void HolidayDto::setName(const string &newName)
    {
        m_Name = newName;
    }

    string HolidayDto::getStartDate() const
    {
        return m_StartDate;
    }

    void HolidayDto::setStartDate(const string &newStartDate)
    {
        m_StartDate = newStartDate;
        m_StartDate.resize(10);
    }

    string HolidayDto::getEndDate() const
    {
        return m_EndDate;
    }

    void HolidayDto::setEndDate(const string &newEndDate)
    {
        m_EndDate = newEndDate;
        m_EndDate.resize(10);
    }

    int HolidayDto::getYear() const
    {
        return m_Year;
    }

    void HolidayDto::setYear(int newYear)
    {
        m_Year = newYear;
    }

    bool HolidayDto::isRecurrence() const
    {
        return m_Recurrence;
    }

    void HolidayDto::setRecurrence(bool newRecurrence)
    {
        m_Recurrence = newRecurrence;
    }

    bool HolidayDto::isActive() const
    {
        return m_Active;
    }

    void HolidayDto::setActive(bool newActive)
    {
        m_Active = newActive;
    }

    void HolidayDto::FromJson(const json &jsonObject)
    {
        if(jsonObject.contains("id")) {
            m_Id = jsonObject["id"];
        }
        m_Name = jsonObject["name"];
        m_StartDate = jsonObject["startDate"]["date"];
        m_StartDate.resize(10);
        m_EndDate = jsonObject["endDate"]["date"];
        m_EndDate.resize(10);
        m_Year = jsonObject["year"];
        m_Recurrence = jsonObject["recurrence"];
        m_Active = jsonObject["active"];
    }

    json HolidayDto::ToJson(bool toSubmit)
    {
        json jsonObject;
        jsonObject["name"] = m_Name;
        jsonObject["startDate"] = m_StartDate;
        jsonObject["endDate"] = m_EndDate;
        jsonObject["year"] = m_Year;
        jsonObject["recurrence"] = m_Recurrence;
        jsonObject["active"] = m_Active;

        if(toSubmit) {
            json retJson;
            retJson["data"] = jsonObject;
            return retJson;
        }
        return jsonObject;
    }
}
