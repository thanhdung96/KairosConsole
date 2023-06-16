#include "App/UserStatus.h"
#include <iterator>
using namespace App;

const string &UserStatus::resolveFromCode(const int &statusCode)
{
    initList();

    return UserStatus::m_StatusTranslateMapping.find(static_cast<UserStatus::Status>(statusCode))->second;
}

const UserStatus::Status &UserStatus::resolveToCode(const string &statusString)
{
    initList();

    Status retStatus;
    for(
        StatusMap::iterator it = UserStatus::m_StatusTranslateMapping.begin();
        it != UserStatus::m_StatusTranslateMapping.begin(); it++
    ) {
        if(it->second == statusString) {
            retStatus = it->first;
        }
    }

    return retStatus;
}

void UserStatus::initList()
{
    if(UserStatus::m_StatusTranslateMapping.empty()) {
        UserStatus::m_StatusTranslateMapping.emplace(UserStatus::Status::Working, "Working");
        UserStatus::m_StatusTranslateMapping.emplace(UserStatus::Status::Quitted, "Quitted");
        UserStatus::m_StatusTranslateMapping.emplace(UserStatus::Status::Fired, "Fired");
        UserStatus::m_StatusTranslateMapping.emplace(UserStatus::Status::EndOfContract, "End of Contract");
    }
}
