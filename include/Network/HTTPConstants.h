#ifndef KAIROSCONSOLE_HTTPCONSTANTS_H
#define KAIROSCONSOLE_HTTPCONSTANTS_H

#include <string>
using namespace std;

namespace Network::Constants {
    enum RequestMethod {
        GET,
        POST,
        PATCH,
        DELETE
    };

    class ApiModel {
        public:
            constexpr static const string Security = "security";
            constexpr static const string App = "app";
            constexpr static const string MyRequest = "my-requests";
            constexpr static const string User = "users";
            constexpr static const string LeaveRequest = "leave-requests";
            constexpr static const string Contact = "contacts";
            constexpr static const string Report = "report";
            constexpr static const string Process = "process";
            constexpr static const string Holiday = "holiday";
            constexpr static const string LeaveType = "leave-types";

        protected:
            ApiModel() = default;
            ~ApiModel() = default;
    };

    class ApiRole {
        public:
            constexpr static const string Admin = "admin";
            constexpr static const string Manager = "manager";
            constexpr static const string User = "user";
        protected:
            ApiRole() = default;
            ~ApiRole() = default;
    };

    class ApiAction {
        public:
            constexpr static const string Login = "login";
            constexpr static const string Activate = "activate";
            constexpr static const string Reset = "reset";
            constexpr static const string Cancel = "cancel";
            constexpr static const string Change = "change";
            constexpr static const string Profile = "profile";
            constexpr static const string ProfileAvatar = "profile/avatar";
            constexpr static const string ProfileNotificationSetting = "profile/setting";
            constexpr static const string List = "list";
            constexpr static const string Summary = "summary";
            constexpr static const string ReportBirthday = "report/birthday";
            constexpr static const string ReportHoliday = "report/holidays";
            /**
             * NOTE: process routes are not properly fixed on backend yet.
             * This action will fail for absolutely sure
             */
            constexpr static const string Process = "process...";
        protected:
            ApiAction() = default;
            ~ApiAction() = default;
    };

    const string DEFAULT_DOMAIN = "https://stg-kairos.bymati.vn/api";
}
#endif //KAIROSCONSOLE_HTTPCONSTANTS_H
