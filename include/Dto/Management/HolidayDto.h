#ifndef HOLIDAYDTO_H
#define HOLIDAYDTO_H

#include "Dto/BaseDto.h"
#include <string>
#include "Network/Helper/json.hpp"

namespace DTO::Management {
using std::string;
using json = nlohmann::json;

    class HolidayDto : public BaseDto
    {
        public:
            HolidayDto() = default;
            ~HolidayDto() = default;

            string getId() const;
            void setId(const string &newId);
            string getName() const;
            void setName(const string &newName);
            string getStartDate() const;
            void setStartDate(const string &newStartDate);
            string getEndDate() const;
            void setEndDate(const string &newEndDate);
            int getYear() const;
            void setYear(int newYear);
            bool isRecurrence() const;
            void setRecurrence(bool newRecurrence);
            bool isActive() const;
            void setActive(bool newActive);

            void FromJson(const json& jsonObject) override;
            json ToJson(bool toSubmit) override;

        private:
            string m_Id;
            string m_Name;
            string m_StartDate;
            string m_EndDate;
            int m_Year;
            bool m_Recurrence;
            bool m_Active;
    };
}

#endif // HOLIDAYDTO_H
