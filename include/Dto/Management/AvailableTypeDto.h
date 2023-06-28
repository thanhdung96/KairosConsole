#ifndef AVAILABLETYPEDTO_H
#define AVAILABLETYPEDTO_H

#include <string>
#include "Dto/BaseDto.h"
#include "Network/Helper/json.hpp"

namespace DTO::Management {
using std::string;
using json = nlohmann::json;

    class AvailableTypeDto : BaseDto
    {
        public:
            AvailableTypeDto() = default;
            ~AvailableTypeDto() = default;

            string getId() const;
            void setId(const string &newId);
            string getName() const;
            void setName(const string &newName);
            string getDescription() const;
            void setDescription(const string &newDescription);
            double getMaximumDay() const;
            void setMaximumDay(double newMaximumDay);
            bool isLeaveToll() const;
            void setLeaveToll(bool newLeaveToll);
            bool isRequireFile() const;
            void setRequireFile(bool newRequireFile);
            bool isUnpaid() const;
            void setUnpaid(bool newUnpaid);
            string getDescriptionRequiredFiles() const;
            void setDescriptionRequiredFiles(const string &newDescriptionRequiredFiles);
            bool isActive() const;
            void setActive(bool newActive);

            void FromJson(const json& jsonObject) override;
            json ToJson(bool toSubmit) override;

        private:
            string m_Id;
            string m_Name;
            string m_Description;
            double m_MaximumDay;
            bool m_LeaveToll;
            bool m_RequireFile;
            bool m_Unpaid;
            string m_DescriptionRequiredFiles;
            bool m_Active;
    };
}

#endif // AVAILABLETYPEDTO_H
