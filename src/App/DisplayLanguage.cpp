#include "App/Displaylanguage.h"
#include <iterator>
using namespace App;

string DisplayLanguage::resolve(const string &key, const ResolveType &resolveType = ResolveType::FromCode)
{
    initList();

    string retData;

    switch (resolveType) {
        case ResolveType::FromCode:
            retData = DisplayLanguage::m_LstSupportedLanguages.find(key)->second;
            break;
        case ResolveType::ToCode:
            retData = DisplayLanguage::m_LstSupportedLanguages.find(key)->first;
            break;
        default:
            break;
    }

    return retData;
}

const LstLanguages DisplayLanguage::getAllLanguagesAndCodes()
{
    initList();
    return DisplayLanguage::m_LstSupportedLanguages;
}

void DisplayLanguage::initList()
{
    if(DisplayLanguage::m_LstSupportedLanguages.empty()) {
        DisplayLanguage::m_LstSupportedLanguages["vi"] = "Tiếng Việt";
        DisplayLanguage::m_LstSupportedLanguages["en"] = "English";
        DisplayLanguage::m_LstSupportedLanguages["fr"] = "Français";
    }
}
