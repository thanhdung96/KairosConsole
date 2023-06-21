#ifndef SETTINGDTO_H
#define SETTINGDTO_H

#include <string>
#include "Dto/BaseDto.h"
#include "Network/Helper/json.hpp"

namespace DTO::App {
using json = nlohmann::json;
using namespace std;

    class SettingDto: BaseDto
    {
        public:
            SettingDto() = default;
            ~SettingDto() = default;

            bool getDailySummary() const;
            void setDailySummary(bool newDailySummary);
            bool getWeeklySummary() const;
            void setWeeklySummary(bool newWeeklySummary);
            bool getMonthlySummary() const;
            void setMonthlySummary(bool newMonthlySummary);
            string getDisplayLanguage() const;
            void setDisplayLanguage(const string &newDisplayLanguage);

            void FromJson(const json& jsonObject) override;
            json ToJson(bool toSubmit);

        private:
            bool m_DailySummary;
            bool m_WeeklySummary;
            bool m_MonthlySummary;
            string m_DisplayLanguage;
    };
}
#endif // SETTINGDTO_H
