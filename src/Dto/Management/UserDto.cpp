#include "Dto/Management/UserDto.h"

namespace DTO::Management {
    string UserDto::getLastName() const
    {
        return m_LastName;
    }

    void UserDto::setLastName(const string &newLastName)
    {
        m_LastName = newLastName;
    }

    string UserDto::getFirstName() const
    {
        return m_FirstName;
    }

    void UserDto::setFirstName(const string &newFirstName)
    {
        m_FirstName = newFirstName;
    }

    string UserDto::getDob() const
    {
        return m_Dob;
    }

    void UserDto::setDob(const string &newDob)
    {
        m_Dob = newDob;
    }

    string UserDto::getFirstWorkDay() const
    {
        return m_FirstWorkDay;
    }

    void UserDto::setFirstWorkDay(const string &newFirstWorkDay)
    {
        m_FirstWorkDay = newFirstWorkDay;
    }

    string UserDto::getPermanentAddress() const
    {
        return m_PermanentAddress;
    }

    void UserDto::setPermanentAddress(const string &newPermanentAddress)
    {
        m_PermanentAddress = newPermanentAddress;
    }

    string UserDto::getTempAddress() const
    {
        return m_TempAddress;
    }

    void UserDto::setTempAddress(const string &newTempAddress)
    {
        m_TempAddress = newTempAddress;
    }

    string UserDto::getCitizenId() const
    {
        return m_CitizenId;
    }

    void UserDto::setCitizenId(const string &newCitizenId)
    {
        m_CitizenId = newCitizenId;
    }

    string UserDto::getSocialInsurranceId() const
    {
        return m_SocialInsurranceId;
    }

    void UserDto::setSocialInsurranceId(const string &newSocialInsurranceId)
    {
        m_SocialInsurranceId = newSocialInsurranceId;
    }

    string UserDto::getMotoBrand() const
    {
        return m_MotoBrand;
    }

    void UserDto::setMotoBrand(const string &newMotoBrand)
    {
        m_MotoBrand = newMotoBrand;
    }

    string UserDto::getPlateNumber() const
    {
        return m_PlateNumber;
    }

    void UserDto::setPlateNumber(const string &newPlateNumber)
    {
        m_PlateNumber = newPlateNumber;
    }

    string UserDto::getPhoneNumber() const
    {
        return m_PhoneNumber;
    }

    void UserDto::setPhoneNumber(const string &newPhoneNumber)
    {
        m_PhoneNumber = newPhoneNumber;
    }

    double UserDto::getSalary() const
    {
        return m_Salary;
    }

    void UserDto::setSalary(double newSalary)
    {
        m_Salary = newSalary;
    }

    string UserDto::getPersonInChargeId() const
    {
        return m_PersonInChargeId;
    }

    void UserDto::setPersonInChargeId(const string &newPersonInChargeId)
    {
        m_PersonInChargeId = newPersonInChargeId;
    }

    string UserDto::getNationality() const
    {
        return m_nationality;
    }

    void UserDto::setNationality(const string &newNationality)
    {
        m_nationality = newNationality;
    }

    string UserDto::getDisplayLanguage() const
    {
        return m_DisplayLanguage;
    }

    void UserDto::setDisplayLanguage(const string &newDisplayLanguage)
    {
        m_DisplayLanguage = newDisplayLanguage;
    }

    void UserDto::FromJson(const json &jsonObject)
    {
        m_LastName = jsonObject["lastName"];
        m_FirstName = jsonObject["firstName"];
        m_Dob = jsonObject["dob"];
        m_FirstWorkDay = jsonObject["firstWorkDay"];
        m_PermanentAddress = jsonObject["permanentAddress"];
        m_TempAddress = jsonObject["tempAddress"];
        m_CitizenId = jsonObject["citizenId"];
        m_SocialInsurranceId = jsonObject["socialInsurranceId"];
        m_MotoBrand = jsonObject["motoBrand"];
        m_PlateNumber = jsonObject["plateNumber"];
        m_PhoneNumber = jsonObject["phoneNumber"];
        m_Salary = jsonObject["salary"];
        m_PersonInChargeId = jsonObject["personInCharge"];
        m_nationality = jsonObject["nationality"];
        m_DisplayLanguage = jsonObject["displayLanguage"];

    }

    json UserDto::ToJson(bool toSubmit)
    {

    }
}

