#include "mainwindow.h"
#include "logindialog.h"
#include "ui_mainwindow.h"
#include <QPushButton>
#include <QEventLoop>
#include <QAction>
#include <QApplication>
#include "Network/Helper/BaseResponse.h"
#include "Network/ApiHandler.h"
#include "Network/Constants/ApiConstants.h"
#include "App/Session.h"
#include "myprofilewidget.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    LoginDialog m_LoginDialog(this);
    bool loginSuccess = m_LoginDialog.exec();
    if(loginSuccess == QDialog::Accepted){
        ui->setupUi(this);
        initialiseUI();
        loadProfile();
    } else if(loginSuccess == QDialog::Rejected) {
        QApplication::quit();
    }
}

MainWindow::~MainWindow()
{

    if(m_MyProfileWg != nullptr) {
        delete m_MyProfileWg;
    }
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

void MainWindow::onActionQuitTriggered(bool checked)
{
    // destroying current widget, if any
    QWidget* currentWidget = ui->swMain->currentWidget();
    if(currentWidget != nullptr) {
        ui->swMain->removeWidget(currentWidget);
        delete currentWidget;
        currentWidget = nullptr;
    }

    QApplication::quit();
}

void MainWindow::onActionMyProfileTriggered(bool checked)
{
    QWidget* currentWidget = ui->swMain->currentWidget();
    if(currentWidget != nullptr) {
        ui->swMain->removeWidget(currentWidget);
        delete currentWidget;
        currentWidget = nullptr;
    }

    if(m_MyProfileWg == nullptr) {
        m_MyProfileWg = new MyProfileWidget;
        ui->swMain->addWidget(m_MyProfileWg);
        this->setWindowTitle("My Profile");
        connect(m_MyProfileWg, SIGNAL(busy(QString)), this, SLOT(onWidgetBusy(QString)));
        connect(m_MyProfileWg, SIGNAL(ready(QString)), this, SLOT(onWidgetReady(QString)));
    }
}

void MainWindow::onWidgetBusy(QString message)
{
    ui->statusbar->showMessage(message);
}

void MainWindow::onWidgetReady(QString message)
{
    ui->statusbar->showMessage(message);
}

void MainWindow::initialiseUI()
{
    connect(ui->actionQuit, SIGNAL(triggered(bool)), this, SLOT(onActionQuitTriggered(bool)));
    connect(ui->actionMyProfile, SIGNAL(triggered(bool)), this, SLOT(onActionMyProfileTriggered(bool)));
}

void MainWindow::loadProfile()
{
    m_ApiHandler.setParent(this);
    m_ApiHandler.setMDomain(Constants::DEFAULT_DOMAIN);
    m_ApiHandler.setMModel(Constants::ApiModel::App);
    m_ApiHandler.setMAction(Constants::ApiAction::Profile);
    m_ApiHandler.Execute(ApiHandler::RequestMethod::GET, SLOT(onFetchProfile(QNetworkReply*)));
}
