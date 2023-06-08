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
    connect(ui->btnShowPassword, SIGNAL(pressed()), this, SLOT(btnShowPasswordPressed()));
    connect(ui->btnShowPassword, SIGNAL(released()), this, SLOT(btnShowPasswordReleased()));

    connect(
        &m_ApiHandler,
        SIGNAL(requestFinished(BaseResponse)),
        this,
        SLOT(getResponse(BaseResponse))
    );
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

    m_ApiHandler.setMDomain(Constants::DEFAULT_DOMAIN);
    m_ApiHandler.setMModel(Constants::ApiModel::Security);
    m_ApiHandler.setMAction(Constants::ApiAction::Login);
    m_ApiHandler.setRequestBody(loginDto.ToJson().dump());
    m_ApiHandler.Execute(ApiHandler::RequestMethod::POST);
}

void LoginDialog::btnShowPasswordPressed()
{
    ui->txtPassword->setEchoMode(QLineEdit::Normal);
}

void LoginDialog::btnShowPasswordReleased()
{
    ui->txtPassword->setEchoMode(QLineEdit::Password);
}

void LoginDialog::getResponse(BaseResponse response)
{
    if(response.ResponseCode() == BaseResponse::Status::HTTP_UNAUTHORIZED) {
        m_LoginSuccess = false;
    } else if (response.ResponseCode() == BaseResponse::Status::HTTP_OK) {
        m_LoginSuccess = true;
        Session::setJwtToken(response.ResponseData("token"));
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
