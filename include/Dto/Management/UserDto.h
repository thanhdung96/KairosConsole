#ifndef USERDTO_H
#define USERDTO_H

#include <string>
#include <vector>
#include "Dto/BaseDto.h"
#include "Network/Helper/json.hpp"

namespace DTO::Management {
using std::string;
using std::vector;
using json = nlohmann::json;

    class UserDto : DTO::BaseDto
    {
        public:
            UserDto() = default;
            ~UserDto() = default;

            string getId() const;
            void setId(const string &newId);
            string getLastName() const;
            void setLastName(const string &newLastName);
            string getFirstName() const;
            void setFirstName(const string &newFirstName);
            string getDob() const;
            void setDob(const string &newDob);
            string getFirstWorkDay() const;
            void setFirstWorkDay(const string &newFirstWorkDay);
            string getPermanentAddress() const;
            void setPermanentAddress(const string &newPermanentAddress);
            string getTempAddress() const;
            void setTempAddress(const string &newTempAddress);
            string getCitizenId() const;
            void setCitizenId(const string &newCitizenId);
            string getSocialInsurranceId() const;
            void setSocialInsurranceId(const string &newSocialInsurranceId);
            string getMotoBrand() const;
            void setMotoBrand(const string &newMotoBrand);
            string getPlateNumber() const;
            void setPlateNumber(const string &newPlateNumber);
            string getPhoneNumber() const;
            void setPhoneNumber(const string &newPhoneNumber);
            double getSalary() const;
            void setSalary(double newSalary);
            string getPersonInChargeId() const;
            void setPersonInChargeId(const string &newPersonInChargeId);
            string getNationality() const;
            void setNationality(const string &newNationality);
            string getDisplayLanguage() const;
            void setDisplayLanguage(const string &newDisplayLanguage);

            void FromJson(const json& jsonObject) override;
            json ToJson(bool toSubmit) override;

        private:
            string m_Id;
            string m_LastName;
            string m_FirstName;
            string m_Dob;
            string m_FirstWorkDay;
            string m_PermanentAddress;
            string m_TempAddress;
            string m_CitizenId;
            string m_SocialInsurranceId;
            string m_MotoBrand;
            string m_PlateNumber;
            string m_PhoneNumber;
            double m_Salary;
            string m_PersonInChargeId;
            string m_nationality;
            string m_DisplayLanguage;
    };
}

#endif // USERDTO_H
