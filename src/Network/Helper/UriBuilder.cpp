#include "Network/Helper/UriBuilder.h"
using namespace Network::Helper;

UriBuilder::UriBuilder() {
    m_LstComponents.insert(UriComponentPair(Component::Scheme, ""));
    m_LstComponents.insert(UriComponentPair(Component::Username, ""));
    m_LstComponents.insert(UriComponentPair(Component::Password, ""));
    m_LstComponents.insert(UriComponentPair(Component::Host, ""));
    m_LstComponents.insert(UriComponentPair(Component::Port, ""));
    m_LstComponents.insert(UriComponentPair(Component::Query, ""));
    m_QuerySeparator = QuerySeparator::ampersand;
}

UriBuilder::~UriBuilder() {
    m_LstComponents.clear();
    m_PathStrings.clear();
    m_QueryStrings.clear();
}

string UriBuilder::toString() {
    string uri = UriBuilder::URI_TEMPLATE;
    string path = getPath();
    string query = getQuery();

    uri.replace(uri.find("$scheme"), 7, this->getScheme());
    if(!this->getUsername().empty()) {
        uri.replace(uri.find("$username"), 9, this->getUsername());

        // check for empty password, if empty remove the second :
        if(!this->getPassword().empty()) {
            uri.replace(uri.find("$password"), 9, this->getPassword());
        } else {
            uri.replace(uri.find("$password"), 9, "");
        }
    } else {
        // if no username provided, remove username and password variable
        uri.replace(uri.find("$username"), 9, "");
        uri.replace(uri.find("$password"), 9, "");
        uri.replace(uri.find(":@"), 2, "");
    }

    uri.replace(uri.find("$host"), 5, this->getHost());

    if(m_IncludePortNumber) {
        uri.replace(uri.find("$port"), 5, this->getPort());
    } else {
        uri.replace(uri.find(":$port"), 6, "");
    }

    uri.replace(uri.find("$path"), 5, path);

    if(!query.empty()) {
        uri.replace(uri.find("$query"), 6, query);
    } else {
        uri.replace(uri.find("?$query"), 7, "");
    }

    if(!m_IncludeLastSlash) {
        uri.replace(uri.find_last_of('/'), 1, "");
    }

    return uri;
}

string UriBuilder::getScheme() {
    return m_LstComponents.find(Component::Scheme)->second;
}

void UriBuilder::setScheme(const string &scheme) {
    m_LstComponents.erase(Component::Scheme);
    m_LstComponents.insert(UriComponentPair(Component::Scheme, scheme));
}

void UriBuilder::setUsername(const string &username) {
    Component componentToReplace = Component::Username;
    m_LstComponents.erase(componentToReplace);
    m_LstComponents.insert(UriComponentPair(componentToReplace, username));
}

string UriBuilder::getUsername() {
    return m_LstComponents.find(Component::Username)->second;
}

string UriBuilder::getPassword() {
    return m_LstComponents.find(Component::Password)->second;
}

void UriBuilder::setPassword(const string &password) {
    Component componentToReplace = Component::Password;
    m_LstComponents.erase(componentToReplace);
    m_LstComponents.insert(UriComponentPair(componentToReplace, password));
}

string UriBuilder::getHost() {
    return m_LstComponents.find(Component::Host)->second;
}

void UriBuilder::setHost(const string &host) {
    Component componentToReplace = Component::Host;
    m_LstComponents.erase(componentToReplace);
    m_LstComponents.insert(UriComponentPair(componentToReplace, host));
}

string UriBuilder::getPort() {
    return m_LstComponents.find(Component::Port)->second;
}

void UriBuilder::setPort(const string &port) {
    Component componentToReplace = Component::Port;
    m_LstComponents.erase(componentToReplace);
    m_LstComponents.insert(UriComponentPair(componentToReplace, port));
}

string UriBuilder::getPath() {
    if(m_PathStrings.empty()) {
        return  "";
    }

    stringstream pathStream;

    for(auto iterator = m_PathStrings.begin(); iterator != m_PathStrings.end(); iterator += 1) {
        if(!(*iterator).empty()) {
            pathStream << *iterator;
            pathStream << PATH_SEPARATOR;
        }
    }

    string path;
    pathStream >> path;
    return path;
}

void UriBuilder::pushPath(const string &path) {
    m_PathStrings.emplace_back(path);
}

void UriBuilder::clearPath() {
    m_PathStrings.clear();
}

string UriBuilder::getQuery() {
    if(m_QueryStrings.empty()) {
        return  "";
    }

    stringstream queryStream;
    string separator = m_QuerySeparator == QuerySeparator::ampersand?
                        QUERY_AMPERSAND_SEPARATOR:
                        QUERY_SEMICOLON_SEPARATOR;

    for(auto iterator = m_QueryStrings.begin(); iterator != m_QueryStrings.end(); iterator += 1) {
        queryStream << *iterator;
        queryStream << separator;
    }

    string query;
    queryStream >> query;
    return query;

}

void UriBuilder::pushQuery(const string &query) {
    m_QueryStrings.emplace_back(query);
}

void UriBuilder::clearQuery() {
    m_QueryStrings.clear();
}

void UriBuilder::setQuerySeparator(const QuerySeparator querySeparator) {
    m_QuerySeparator = querySeparator;
}

UriBuilder::QuerySeparator UriBuilder::getQuerySeparator() {
    return m_QuerySeparator;
}

bool UriBuilder::isMIncludePortNumber() {
    return m_IncludePortNumber;
}

void UriBuilder::setMIncludePortNumber(bool mIncludePortNumber) {
    m_IncludePortNumber = mIncludePortNumber;
}

bool UriBuilder::isMIncludeLastSlash() {
    return m_IncludeLastSlash;
}

void UriBuilder::setMIncludeLastSlash(bool mIncludeLastSlash) {
    m_IncludeLastSlash = mIncludeLastSlash;
}
