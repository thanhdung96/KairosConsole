#ifndef USERROLE_H
#define USERROLE_H

#include <string>
#include <map>
using namespace std;

namespace App {
typedef map<string, string> UserRoleMap;

    class UserRole
    {
        public:
            inline static const string SadminCode = "ROLE_SUPER_ADMIN";
            inline static const string AdminCode = "ROLE_ADMIN";
            inline static const string ManagerCode = "ROLE_MANAGER";
            inline static const string EmployeeCode = "ROLE_EMPLOYEE";
            inline static const string InternCode = "ROLE_INTERN";
            inline static const string PartTimerCode = "ROLE_PTIME";
            inline static const string FreelancerCode = "ROLE_FREELANCE";

        public:
            static const string& resolveCode(const string& roleCode);
            static const string& resolveName(const string& roleName);
            static const string& getNameFromCode(const string& roleCode);

        private:
            UserRole() = default;
            ~UserRole() = default;
            static void initListCode();
            static void initListName();

        private:
            inline static UserRoleMap m_RoleTranslateMapping;
            inline static UserRoleMap m_RoleNameMapping;
    };
}

#endif // USERROLE_H
