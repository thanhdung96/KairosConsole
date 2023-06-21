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
            static const string& getUsername();
            static void setUsername(const string &newUsername);
            static const string& getEmail();
            static void setEmail(const string &newEmail);
            static string getRole();
            static void setRole(const string &newRole);

        private:
            Session() = default;
            ~Session() = default;

        private:
            inline static string m_JwtToken;
            inline static string m_Username;
            inline static string m_Email;
            inline static string m_Role;
    };
}

#endif // SESSION_H
