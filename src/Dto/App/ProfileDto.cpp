#include "Dto/App/ProfileDto.h"
using namespace DTO::App;

ProfileDto::ProfileDto()
{

}

string ProfileDto::getLastName() const
{
    return m_LastName;
}

void ProfileDto::setLastName(const string &newLastName)
{
    m_LastName = newLastName;
}

string ProfileDto::getFirstName() const
{
    return m_FirstName;
}

void ProfileDto::setFirstName(const string &newFirstName)
{
    m_FirstName = newFirstName;
}

string ProfileDto::getCitizenId() const
{
    return m_CitizenId;
}

void ProfileDto::setCitizenId(const string &newCitizenId)
{
    m_CitizenId = newCitizenId;
}

string ProfileDto::getSocialInsurranceId() const
{
    return m_SocialInsurranceId;
}

void ProfileDto::setSocialInsurranceId(const string &newSocialInsurranceId)
{
    m_SocialInsurranceId = newSocialInsurranceId;
}

string ProfileDto::getMotoBrand() const
{
    return m_MotoBrand;
}

void ProfileDto::setMotoBrand(const string &newMotoBrand)
{
    m_MotoBrand = newMotoBrand;
}

string ProfileDto::getPlateNumber() const
{
    return m_PlateNumber;
}

void ProfileDto::setPlateNumber(const string &newPlateNumber)
{
    m_PlateNumber = newPlateNumber;
}

string ProfileDto::getTempAddress() const
{
    return m_TempAddress;
}

void ProfileDto::setTempAddress(const string &newTempAddress)
{
    m_TempAddress = newTempAddress;
}

string ProfileDto::getPermanentAddress() const
{
    return m_PermanentAddress;
}

void ProfileDto::setPermanentAddress(const string &newPermanentAddress)
{
    m_PermanentAddress = newPermanentAddress;
}

string ProfileDto::getPhoneNumber() const
{
    return m_PhoneNumber;
}

void ProfileDto::setPhoneNumber(const string &newPhoneNumber)
{
    m_PhoneNumber = newPhoneNumber;
}

string ProfileDto::getNationality() const
{
    return m_Nationality;
}

void ProfileDto::setNationality(const string &newNationality)
{
    m_Nationality = newNationality;
}

string ProfileDto::getFirstWorkingDay() const
{
    return m_FirstWorkingDay;
}

void ProfileDto::setFirstWorkingDay(const string &newFirstWorkingDay)
{
    m_FirstWorkingDay = newFirstWorkingDay;
}

int ProfileDto::getStatus() const
{
    return m_Status;
}

void ProfileDto::setStatus(int newStatus)
{
    m_Status = newStatus;
}

string ProfileDto::getEmpCode() const
{
    return m_EmpCode;
}

void ProfileDto::setEmpCode(const string &newEmpCode)
{
    m_EmpCode = newEmpCode;
}

string ProfileDto::getEmail() const
{
    return m_Email;
}

void ProfileDto::setEmail(const string &newEmail)
{
    m_Email = newEmail;
}

string ProfileDto::getDob() const
{
    return m_Dob;
}

void ProfileDto::setDob(const string &newDob)
{
    m_Dob = newDob;
}

const json ProfileDto::toJson(bool toSubmit)
{
    json js;
    if(!m_LastName.empty()) {
        js["lastName"] = m_LastName;
    }
    if(!m_FirstName.empty()) {
        js["firstName"] = m_FirstName;
    }
    if(!m_CitizenId.empty()) {
        js["citizenId"] = m_CitizenId;
    }
    if(!m_SocialInsurranceId.empty()) {
        js["socialInsurranceId"] = m_SocialInsurranceId;
    }
    if(!m_MotoBrand.empty()) {
        js["motoBrand"] = m_MotoBrand;
    }
    if(!m_PlateNumber.empty()) {
        js["plateNumber"] = m_PlateNumber;
    }
    if(!m_TempAddress.empty()) {
        js["tempAddress"] = m_TempAddress;
    }
    if(!m_PermanentAddress.empty()) {
        js["permanentAddress"] = m_PermanentAddress;
    }
    if(!m_PhoneNumber.empty()) {
        js["phoneNumber"] = m_PhoneNumber;
    }
    if(!m_Nationality.empty()) {
        js["nationality"] = m_Nationality;
    }
    if(!m_FirstWorkingDay.empty()) {
        js["firstWorkDay"] = m_FirstWorkingDay;
    }
    if(!toSubmit) {
        js["status"] = m_Status;
    }
    if(!m_EmpCode.empty()) {
        js["account"]["empCode"] = m_EmpCode;
    }
    if(!m_Email.empty()) {
        js["account"]["email"] = m_Email;
    }

    if(toSubmit) {
        json retJson;
        retJson["data"] = js;
        return retJson;
    } else {
        return js;
    }
}

void ProfileDto::fromJson(const json &js)
{
    json userJson = js["user"];
    json accountJson = js["account"];
    m_LastName = userJson["lastName"];
    m_FirstName = userJson["firstName"];
    m_CitizenId = userJson["citizenId"];
    m_Dob = userJson["dob"]["date"];
    m_Dob.resize(DATE_STRING_SIZE);
    m_SocialInsurranceId = userJson["socialInsurranceId"];
    m_MotoBrand = userJson["motoBrand"];
    m_PlateNumber = userJson["plateNumber"];
    m_TempAddress = userJson["tempAddress"];
    m_PermanentAddress = userJson["permanentAddress"];
    m_PhoneNumber = userJson["phoneNumber"];
    m_Nationality = userJson["nationality"];
    m_FirstWorkingDay = userJson["firstWorkDay"]["date"];
    m_FirstWorkingDay.resize(DATE_STRING_SIZE);
    m_Status = userJson["status"];
    m_EmpCode = accountJson["empCode"];
    m_Email = accountJson["email"];
}
