#ifndef PROFILEDTO_H
#define PROFILEDTO_H

#include <string>
#include "Network/Helper/json.hpp"

namespace DTO::App {
using namespace std;
using json = nlohmann::json;

    class ProfileDto
    {
        public:
            ProfileDto();

            string getLastName() const;
            void setLastName(const string &newLastName);
            string getFirstName() const;
            void setFirstName(const string &newFirstName);
            string getCitizenId() const;
            void setCitizenId(const string &newCitizenId);
            string getSocialInsurranceId() const;
            void setSocialInsurranceId(const string &newSocialInsurranceId);
            string getMotoBrand() const;
            void setMotoBrand(const string &newMotoBrand);
            string getPlateNumber() const;
            void setPlateNumber(const string &newPlateNumber);
            string getTempAddress() const;
            void setTempAddress(const string &newTempAddress);
            string getPermanentAddress() const;
            void setPermanentAddress(const string &newPermanentAddress);
            string getPhoneNumber() const;
            void setPhoneNumber(const string &newPhoneNumber);
            string getNationality() const;
            void setNationality(const string &newNationality);
            string getFirstWorkingDay() const;
            void setFirstWorkingDay(const string &newFirstWorkingDay);
            string getDisplayLanguage() const;
            void setDisplayLanguage(const string &newDisplayLanguage);
            int getStatus() const;
            void setStatus(int newStatus);
            string getEmpCode() const;
            void setEmpCode(const string &newEmpCode);
            string getEmail() const;
            void setEmail(const string &newEmail);
            string getDob() const;
            void setDob(const string &newDob);

            const json toJson(bool toSubmit);
            void fromJson(const json& js);

        private:
            string m_LastName;
            string m_FirstName;
            string m_CitizenId;
            string m_SocialInsurranceId;
            string m_Dob;
            string m_MotoBrand;
            string m_PlateNumber;
            string m_TempAddress;
            string m_PermanentAddress;
            string m_PhoneNumber;
            string m_Nationality;
            string m_DisplayLanguage;
            string m_FirstWorkingDay;
            int m_Status;
            string m_EmpCode;
            string m_Email;

            const size_t DATE_STRING_SIZE = 10;
    };
}
#endif // PROFILEDTO_H
