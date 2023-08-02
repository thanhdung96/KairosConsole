#ifndef CONTACTPERSON_H
#define CONTACTPERSON_H

#include <string>
#include "Dto/BaseDto.h"
#include "Network/Helper/json.hpp"

namespace DTO::Management {
using std::string;
using json = nlohmann::json;

    class ContactPerson : DTO::BaseDto
    {
        public:
            ContactPerson() = default;
            ~ContactPerson() = default;

            string getFullname() const;
            void setFullname(const string &newFullname);
            string getAddress() const;
            void setAddress(const string &newAddress);
            string Email() const;
            void setEmail(const string &newEmail);
            string getPhoneNumber() const;
            void setPhoneNumber(const string &newPhoneNumber);
            string getRelationship() const;
            void setRelationship(const string &newRelationship);

            void FromJson(const json& jsonObject) override;
            json ToJson(bool toSubmit) override;

        private:
            string m_Fullname;
            string m_Address;
            string m_Email;
            string m_PhoneNumber;
            string m_Relationship;
    };
}

#endif // CONTACTPERSON_H
