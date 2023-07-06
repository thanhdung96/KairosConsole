#include "App/Displaylanguage.h"

namespace App {
    string DisplayLanguage::resolve(const string &key, const ResolveType &resolveType = ResolveType::FromCode)
    {
        initList();

        string retData;
        switch (resolveType) {
        case ResolveType::FromCode:
            retData = DisplayLanguage::m_LstSupportedLanguages.find(key)->second;
            break;
        case ResolveType::ToCode:
            for(
                LanguageMappingIterator it = DisplayLanguage::m_LstSupportedLanguages.begin();
                it != DisplayLanguage::m_LstSupportedLanguages.end();
                it++
            ) {
                if(it->second == key) {
                    retData = it->first;
                    break;
                }
            }
        default:
            break;
        }

        return retData;
    }

    const LstLanguage DisplayLanguage::getAllLanguages()
    {
        initList();
        LstLanguage lstLanguages;

        for(
            LanguageMappingIterator it = DisplayLanguage::m_LstSupportedLanguages.begin();
            it != DisplayLanguage::m_LstSupportedLanguages.end();
            it++
            ) {
            lstLanguages.emplace_back(it->second);
        }

        return lstLanguages;
    }

    void DisplayLanguage::initList()
    {
        if(DisplayLanguage::m_LstSupportedLanguages.empty()) {
            DisplayLanguage::m_LstSupportedLanguages["vi"] = "Tiếng Việt";
            DisplayLanguage::m_LstSupportedLanguages["en"] = "English";
            DisplayLanguage::m_LstSupportedLanguages["fr"] = "Français";
        }
    }
}
