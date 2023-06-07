#include "logindialog.h"
#include "ui_logindialog.h"

LoginDialog::LoginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginDialog)
{
    ui->setupUi(this);
    this->loginSuccess = false;

    connect(ui->btnCancel, SIGNAL(clicked()), this, SLOT(btnCancelClicked()));
    connect(ui->btnLogin, SIGNAL(clicked()), this, SLOT(btnLoginClicked()));
}

LoginDialog::~LoginDialog()
{
    delete ui;
}

void LoginDialog::btnCancelClicked() {
    this->close();
}

void LoginDialog::btnLoginClicked() {
    string username;
    string password;
    LoginDto loginDto("sadmin", "Change_m3");
    string requestBody = loginDto.ToJson().dump();

    ApiHandler apiHandler;
    apiHandler.setMDomain(Constants::DEFAULT_DOMAIN);
    apiHandler.setMModel(Constants::ApiModel::Security);
    apiHandler.setMAction(Constants::ApiAction::Login);
    apiHandler.setRequestBody(requestBody);
    ui->txtTextEdit->setText(
        QString::fromStdString(apiHandler.Execute(ApiHandler::RequestMethod::POST))
    );
}

bool LoginDialog::getLoginSuccess() const
{
    return loginSuccess;
}

void LoginDialog::setLoginSuccess(bool newLoginSuccess)
{
    loginSuccess = newLoginSuccess;
}
