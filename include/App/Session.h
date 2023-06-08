#ifndef SESSION_H
#define SESSION_H

#include <string>

namespace App {
    using namespace std;

    class Session
    {
        public:
            static const string& getJwtToken();
            static void setJwtToken(const string &newJwtToken);

        private:
            Session() = default;
            ~Session() = default;

        private:
            inline static string m_JwtToken;
    };
}

#endif // SESSION_H
