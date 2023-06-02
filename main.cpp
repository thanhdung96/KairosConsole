#include <iostream>
#include "Network/ApiHandler.h"
#include "Network/HTTPConstants.h"
#include "Dto/Security/LoginDto.h"
using namespace Network;
using namespace DTO::Security;
using namespace std;

int main()
{
    LoginDto loginDto("sadmin", "Change_m3");
    string requestBody = loginDto.ToJson().dump();

    ApiHandler apiHandler;
    apiHandler.setMDomain(Constants::DEFAULT_DOMAIN);
    apiHandler.setMModel(Constants::ApiModel::Security);
    apiHandler.setMAction(Constants::ApiAction::Login);
    apiHandler.setRequestBody(requestBody);
    cout << apiHandler.Execute(Constants::RequestMethod::POST) << endl;

    return 0;
}
