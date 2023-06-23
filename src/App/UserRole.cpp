#include "App/UserRole.h"

namespace App {
    const string &UserRole::resolveCode(const string &roleCode)
    {
        initListCode();

        return UserRole::m_RoleTranslateMapping.find(roleCode)->second;
    }

    const string &UserRole::resolveName(const string &roleName)
    {
        initListName();
        for(
            UserRoleMap::iterator itor = UserRole::m_RoleNameMapping.begin();
             itor != UserRole::m_RoleNameMapping.end();
            itor++
        ) {
            if(itor->second == roleName) {
                return itor->first;
            }
        }

        return string();
    }

    const string &UserRole::getNameFromCode(const string &roleCode)
    {
        initListName();

        return UserRole::m_RoleNameMapping.find(roleCode)->second;
    }

    void UserRole::initListCode()
    {
        // some roles have same code, intentionally
        if(UserRole::m_RoleTranslateMapping.empty()) {
            UserRole::m_RoleTranslateMapping[UserRole::SadminCode] = "admin";
            UserRole::m_RoleTranslateMapping[UserRole::AdminCode] = "admin";
            UserRole::m_RoleTranslateMapping[UserRole::ManagerCode] = "manager";
            UserRole::m_RoleTranslateMapping[UserRole::EmployeeCode] = "user";
            UserRole::m_RoleTranslateMapping[UserRole::PartTimerCode] = "user";
            UserRole::m_RoleTranslateMapping[UserRole::FreelancerCode] = "user";
            UserRole::m_RoleTranslateMapping[UserRole::InternCode] = "user";
        }
    }

    void UserRole::initListName()
    {
        if(UserRole::m_RoleNameMapping.empty()) {
            UserRole::m_RoleNameMapping[UserRole::SadminCode] = "Super Admin";
            UserRole::m_RoleNameMapping[UserRole::AdminCode] = "Admin";
            UserRole::m_RoleNameMapping[UserRole::ManagerCode] = "Manager";
            UserRole::m_RoleNameMapping[UserRole::EmployeeCode] = "Employe";
            UserRole::m_RoleNameMapping[UserRole::InternCode] = "Internship";
            UserRole::m_RoleNameMapping[UserRole::PartTimerCode] = "Part-timer";
            UserRole::m_RoleNameMapping[UserRole::FreelancerCode] = "Freelancer";
        }
    }
}
