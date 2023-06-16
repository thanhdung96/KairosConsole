#ifndef DISPLAYLANGUAGE_H
#define DISPLAYLANGUAGE_H

#include <map>
#include <string>

namespace App {
    using namespace std;
    typedef map<string, string> LstLanguages;

    class DisplayLanguage
    {
        public:
            enum class ResolveType {
                FromCode,
                ToCode
            };

            static string resolve(const string& key, const ResolveType& resolveType);
            static const LstLanguages getAllLanguagesAndCodes();

        private:
            DisplayLanguage() = default;
            ~DisplayLanguage() = default;
            static void initList();

        private:
            inline static LstLanguages m_LstSupportedLanguages;
    };
}

#endif // DISPLAYLANGUAGE_H
