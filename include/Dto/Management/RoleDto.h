#ifndef ROLEDTO_H
#define ROLEDTO_H

#include <string>
#include <QMetaType>
#include "Dto/BaseDto.h"
#include "Network/Helper/json.hpp"

namespace DTO::Management {
using json = nlohmann::json;
using namespace std;

    class RoleDto : DTO::BaseDto
    {
        public:
            RoleDto() = default;
            ~RoleDto() = default;

            string getId() const;
            void setId(const string &newId);
            string getName() const;
            void setName(const string &newName);
            string getDescription() const;
            void setDescription(const string &newDescription);
            int getMaxLeaveBalance() const;
            void setMaxLeaveBalance(int newMaxLeaveBalance);
            bool isActive() const;
            void setActive(bool newActive);
            string getCode() const;
            void setCode(const string &newCode);

            void FromJson(const json& jsonObject) override;
            json ToJson(bool toSubmit) override;

        private:
            string m_Id;
            string m_Name;
            string m_Description;
            int m_MaxLeaveBalance;
            bool m_Active;
            string m_Code;
    };
}

Q_DECLARE_METATYPE(DTO::Management::RoleDto);
#endif // ROLEDTO_H
