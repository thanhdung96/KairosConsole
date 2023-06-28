#ifndef USERSTATUS_H
#define USERSTATUS_H

#include <map>
#include <string>

namespace App {
using std::map, std::string;
typedef map<int, string> StatusMap;

    class UserStatus
    {
    public:
        enum class Status {
            Working,
            Quitted,
            Fired,
            EndOfContract
        };
        typedef map<Status, string> StatusMap;

        static const string& resolveFromCode(const int& statusCode);
        static const Status& resolveToCode(const string& statusString);

        private:
            UserStatus() = default;
            ~UserStatus() = default;
            static void initList();

        private:
            inline static StatusMap m_StatusTranslateMapping;
    };
}

#endif // USERSTATUS_H
