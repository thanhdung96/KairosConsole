#ifndef KAIROSCONSOLE_URIBUILDER_H
#define KAIROSCONSOLE_URIBUILDER_H

#include <map>
#include <vector>
#include <string>
#include <sstream>

namespace Network::Helper{
    using namespace std;

    class UriBuilder {
        public:
            enum class Component
            {
                Scheme,
                Username,
                Password,
                Host,
                Port,
                Path,
                Query
            };
            enum class QuerySeparator
            {
                ampersand,
                semicolon
            };

            UriBuilder();
            ~UriBuilder();
            string toString();

            string getScheme();
            void setScheme(const string& scheme);
            string getUsername();
            void setUsername(const string& username);
            string getPassword();
            void setPassword(const string& password);
            string getHost();
            void setHost(const string& host);
            string getPort();
            void setPort(const string& port);
            string getPath();
            void pushPath(const string& path);
            void clearPath();
            string getQuery();
            void pushQuery(const string& query);
            void clearQuery();
            void setQuerySeparator(QuerySeparator querySeparator);
            QuerySeparator getQuerySeparator();
            bool isMIncludePortNumber();
            void setMIncludePortNumber(bool mIncludePortNumber);
            bool isMIncludeLastSlash();
            void setMIncludeLastSlash(bool mIncludeLastSlash);

        private:
            map<Component, string> m_LstComponents;
            vector<string> m_PathStrings;
            vector<string> m_QueryStrings;
            QuerySeparator m_QuerySeparator;

            bool m_IncludePortNumber;
            bool m_IncludeLastSlash;

            const string URI_TEMPLATE= "$scheme://$username:$password@$host:$port/$path?$query";
            const string PATH_SEPARATOR = "/";
            const string QUERY_AMPERSAND_SEPARATOR = "&";
            const string QUERY_SEMICOLON_SEPARATOR = ";";
    };

    typedef pair<UriBuilder::Component, string> UriComponentPair;
}
#endif //KAIROSCONSOLE_URIBUILDER_H
