#ifndef DISPLAYLANGUAGE_H
#define DISPLAYLANGUAGE_H

#include <map>
#include <vector>
#include <string>

namespace App {
using std::map, std::string, std::vector;
typedef map<string, string> LstLanguageMapping;
typedef LstLanguageMapping::iterator LanguageMappingIterator;
typedef vector<string> LstLanguage;

    class DisplayLanguage
    {
        public:
            enum class ResolveType {
                FromCode,
                ToCode
            };

            static string resolve(const string& key, const ResolveType& resolveType);
            static const LstLanguage getAllLanguages();

        private:
            DisplayLanguage() = default;
            ~DisplayLanguage() = default;
            static void initList();

        private:
            inline static LstLanguageMapping m_LstSupportedLanguages;
    };
}

#endif // DISPLAYLANGUAGE_H
