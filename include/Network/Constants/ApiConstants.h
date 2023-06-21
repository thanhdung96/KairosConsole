#ifndef KAIROSCONSOLE_APICONSTANTS_H
#define KAIROSCONSOLE_APICONSTANTS_H

#include <string>
#include <vector>
using namespace std;

namespace Network::Constants {
    inline const string DEFAULT_DOMAIN = "stg-kairos.bymati.vn/api";
    inline const string HTTPS_SCHEME = "https";
    inline const string HTTPS_PORT = "443";

    class ApiModel {
        public:
            inline static const string Security = "security";
            inline static const string App = "app";
            inline static const string MyRequest = "my-requests";
            inline static const string User = "users";
            inline static const string LeaveRequest = "leave-requests";
            inline static const string Contact = "contacts";
            inline static const string Report = "report";
            inline static const string Process = "process";
            inline static const string Holiday = "holiday";
            inline static const string LeaveType = "leave-types";

            inline static const vector<string> ModelWithoutRole = {
                Security,
                App
            };

        protected:
            ApiModel() = default;
            ~ApiModel() = default;
    };

    class ApiRole {
        public:
            inline static const string Admin = "admin";
            inline static const string Manager = "manager";
            inline static const string User = "user";
        protected:
            ApiRole() = default;
            ~ApiRole() = default;
    };

    class ApiAction {
        public:
            inline static const string Login = "login";
            inline static const string Activate = "activate";
            inline static const string Reset = "reset";
            inline static const string Cancel = "cancel";
            inline static const string Change = "change";
            inline static const string Profile = "profile";
            inline static const string ProfileAvatar = "profile/avatar";
            inline static const string ProfileSetting = "profile/setting";
            inline static const string List = "list";
            inline static const string Summary = "summary";
            inline static const string ReportBirthday = "report/birthday";
            inline static const string ReportHoliday = "report/holidays";
            /**
             * NOTE: process routes are not properly fixed on backend yet.
             * This action will fail for absolutely sure
             */
            inline static const string Process = "process...";
        protected:
            ApiAction() = default;
            ~ApiAction() = default;
    };
}
#endif //KAIROSCONSOLE_APICONSTANTS_H
