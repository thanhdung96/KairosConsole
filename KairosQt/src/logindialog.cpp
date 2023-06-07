#include "logindialog.h"
#include "ui_logindialog.h"

LoginDialog::LoginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginDialog)
{
    ui->setupUi(this);
    this->m_LoginSuccess = false;

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
    LoginDto loginDto(
        ui->txtUsername->text().toStdString(),
        ui->txtPassword->text().toStdString()
    );
    string requestBody = loginDto.ToJson().dump();

    m_ApiHandler.setMDomain(Constants::DEFAULT_DOMAIN);
    m_ApiHandler.setMModel(Constants::ApiModel::Security);
    m_ApiHandler.setMAction(Constants::ApiAction::Login);
    m_ApiHandler.setRequestBody(requestBody);
    BaseResponse response = m_ApiHandler.Execute(ApiHandler::RequestMethod::POST);

    if(response.ResponseCode() == BaseResponse::Status::HTTP_UNAUTHORIZED) {
        m_LoginSuccess = false;
    } else if (response.ResponseCode() == BaseResponse::Status::HTTP_OK) {
        m_LoginSuccess = true;
        this->close();
    }
}

bool LoginDialog::getLoginSuccess() const
{
    return m_LoginSuccess;
}

void LoginDialog::setLoginSuccess(bool newLoginSuccess)
{
    m_LoginSuccess = newLoginSuccess;
}
