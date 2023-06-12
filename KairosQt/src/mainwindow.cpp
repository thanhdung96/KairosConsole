#include "mainwindow.h"
#include "logindialog.h"
#include "ui_mainwindow.h"
#include <QString>
#include <QEventLoop>
#include "Network/Helper/BaseResponse.h"
#include "Network/ApiHandler.h"
#include "Network/Constants/ApiConstants.h"
#include "App/Session.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    LoginDialog m_LoginDialog(this);
    bool loginSuccess = m_LoginDialog.exec();
    if(loginSuccess == QDialog::Accepted){
        ui->setupUi(this);

        m_ApiHandler.setParent(this);
        m_ApiHandler.setMDomain(Constants::DEFAULT_DOMAIN);
        m_ApiHandler.setMModel(Constants::ApiModel::App);
        m_ApiHandler.setMAction(Constants::ApiAction::Profile);
        m_ApiHandler.Execute(ApiHandler::RequestMethod::GET, SLOT(onFetchProfile(QNetworkReply*)));

    } else if(loginSuccess == QDialog::Rejected) {
        this->close();
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onFetchProfile(QNetworkReply* reply)
{
    QEventLoop eventLoop;
    connect(reply, SIGNAL(finished()), &eventLoop, SLOT(quit()));
    BaseResponse response(
        reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt(),
        QString(reply->readAll()).toStdString()
    );
    reply->deleteLater();

    App::Session::setEmail(response.getResponseData()["account"]["email"]);
    App::Session::setUsername(response.getResponseData()["account"]["empCode"]);
}
