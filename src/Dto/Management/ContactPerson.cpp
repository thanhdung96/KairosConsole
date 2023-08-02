#include "Dto/Management/ContactPerson.h"

namespace DTO::Management {
    string ContactPerson::getFullname() const
    {
        return m_Fullname;
    }

    void ContactPerson::setFullname(const string &newFullname)
    {
        m_Fullname = newFullname;
    }

    string ContactPerson::getAddress() const
    {
        return m_Address;
    }

    void ContactPerson::setAddress(const string &newAddress)
    {
        m_Address = newAddress;
    }

    string ContactPerson::Email() const
    {
        return m_Email;
    }

    void ContactPerson::setEmail(const string &newEmail)
    {
        m_Email = newEmail;
    }

    string ContactPerson::getPhoneNumber() const
    {
        return m_PhoneNumber;
    }

    void ContactPerson::setPhoneNumber(const string &newPhoneNumber)
    {
        m_PhoneNumber = newPhoneNumber;
    }

    string ContactPerson::getRelationship() const
    {
        return m_Relationship;
    }

    void ContactPerson::setRelationship(const string &newRelationship)
    {
        m_Relationship = newRelationship;
    }

    void ContactPerson::FromJson(const json &jsonObject)
    {
        m_Fullname = jsonObject["fullname"];
        m_Address = jsonObject["address"];
        m_Email = jsonObject["email"];
        m_PhoneNumber = jsonObject["phoneNumber"];
        m_Relationship = jsonObject["relationship"];
    }

    json ContactPerson::ToJson(bool toSubmit)
    {
        json jsonObject;
        jsonObject["fullname"] = m_Fullname;
        jsonObject["address"] = m_Address;
        jsonObject["email"] = m_Email;
        jsonObject["phoneNumber"] = m_PhoneNumber;
        jsonObject["relationship"] = m_Relationship;

        if(toSubmit) {
            json retJson;
            retJson["data"] = jsonObject;
            return retJson;
        }
        return jsonObject;

    }
}
