#ifndef COUNTRYCODE_H
#define COUNTRYCODE_H

#include <string>

namespace App {
using std::string;
    class CountryCode
    {
        public:
            inline static const string British = "br";
            inline static const string French = "fr";
            inline static const string Vietnam = "vi";

        private:
            CountryCode() = default;
            ~CountryCode() = default;
    };
}

#endif // COUNTRYCODE_H
