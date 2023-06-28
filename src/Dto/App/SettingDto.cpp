#include "Dto/App/SettingDto.h"

namespace DTO::App {
    bool SettingDto::getDailySummary() const
    {
        return m_DailySummary;
    }

    void SettingDto::setDailySummary(bool newDailySummary)
    {
        m_DailySummary = newDailySummary;
    }

    bool SettingDto::getWeeklySummary() const
    {
        return m_WeeklySummary;
    }

    void SettingDto::setWeeklySummary(bool newWeeklySummary)
    {
        m_WeeklySummary = newWeeklySummary;
    }

    bool SettingDto::getMonthlySummary() const
    {
        return m_MonthlySummary;
    }

    void SettingDto::setMonthlySummary(bool newMonthlySummary)
    {
        m_MonthlySummary = newMonthlySummary;
    }

    string SettingDto::getDisplayLanguage() const
    {
        return m_DisplayLanguage;
    }

    void SettingDto::setDisplayLanguage(const string &newDisplayLanguage)
    {
        m_DisplayLanguage = newDisplayLanguage;
    }

    void SettingDto::FromJson(const json &jsonObject)
    {
        m_DailySummary = jsonObject["dailySummary"];
        m_WeeklySummary = jsonObject["weeklySummary"];
        m_MonthlySummary = jsonObject["monthlySummary"];
        m_DisplayLanguage = jsonObject["displayLanguage"];
    }

    json SettingDto::ToJson(bool toSubmit)
    {
        json jsonObject;
        jsonObject["dailySummary"] = m_DailySummary;
        jsonObject["weeklySummary"] = m_WeeklySummary;
        jsonObject["monthlySummary"] = m_MonthlySummary;
        jsonObject["displayLanguage"] = m_DisplayLanguage;

        if(toSubmit) {
            json retJson;
            retJson["data"] = jsonObject;
            return retJson;
        }

        return jsonObject;
    }
}
