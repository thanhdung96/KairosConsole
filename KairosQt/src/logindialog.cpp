#include "logindialog.h"
#include "ui_logindialog.h"
#include "Dto/Security/LoginDto.h"
#include "App/Session.h"
#include "Network/Constants/ApiConstants.h"
#include "Network/Helper/BaseResponse.h"
#include <QEventLoop>
#include <QPushButton>
#include <QLineEdit>
#include <QString>

using namespace Network::Helper;
using namespace DTO::Security;

LoginDialog::LoginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginDialog)
{
    m_LoginSuccess = false;
    ui->setupUi(this);
    ui->progressBar->hide();
    ui->txtStatus->setText("Please provide your ID and password.");

    m_ApiHandler.setParent(this);

    connect(ui->btnCancel, &QPushButton::clicked, this, &LoginDialog::btnCancelClicked);
    connect(ui->btnLogin, &QPushButton::clicked, this, &LoginDialog::btnLoginClicked);
    connect(ui->btnShowPassword, &QPushButton::pressed, this, &LoginDialog::btnShowPasswordPressed);
    connect(ui->btnShowPassword, &QPushButton::released, this, &LoginDialog::btnShowPasswordReleased);
}

LoginDialog::~LoginDialog()
{
    delete ui;
}

void LoginDialog::btnCancelClicked() {
    this->close();
}

void LoginDialog::btnLoginClicked() {
    ui->progressBar->hide();
    ui->txtStatus->setText("Checking credential...");

    LoginDto loginDto(
        ui->txtUsername->text().toStdString(),
        ui->txtPassword->text().toStdString()
    );

    m_ApiHandler.setMDomain(Constants::DEFAULT_DOMAIN);
    m_ApiHandler.setMModel(Constants::ApiModel::Security);
    m_ApiHandler.setMAction(Constants::ApiAction::Login);
    m_ApiHandler.setRequestBody(loginDto.ToJson().dump());
    m_ApiHandler.Execute(ApiHandler::RequestMethod::POST, SLOT(onFinished(QNetworkReply*)));
    ui->progressBar->show();
}

void LoginDialog::btnShowPasswordPressed()
{
    ui->txtPassword->setEchoMode(QLineEdit::Normal);
}

void LoginDialog::btnShowPasswordReleased()
{
    ui->txtPassword->setEchoMode(QLineEdit::Password);
}

void LoginDialog::onFinished(QNetworkReply* reply)
{
    ui->progressBar->hide();
    QEventLoop eventLoop;
    connect(reply, SIGNAL(finished()), &eventLoop, SLOT(quit()));
    BaseResponse response(
        reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt(),
        QString(reply->readAll()).toStdString()
    );
    reply->deleteLater();

    m_LoginSuccess = response.ResponseCode() == BaseResponse::Status::HTTP_OK;
    if(m_LoginSuccess) {
        App::Session::setJwtToken(response.getResponseData()["token"]);
        this->close();
    } else {
        ui->txtStatus->setText("Invalid credential.");
    }
}

void LoginDialog::closeEvent(QCloseEvent* event)
{
    if(m_LoginSuccess) {
        this->done(QDialog::Accepted);
    } else {
        this->done(QDialog::Rejected);
    }
    event->accept();
}
