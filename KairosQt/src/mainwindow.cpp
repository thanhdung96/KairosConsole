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
    if(m_PreferenceWg != nullptr) {
        delete m_PreferenceWg;
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
    App::Session::setRole(response.getResponseData()["account"]["role"]);
}

void MainWindow::onActionQuitTriggered(bool checked)
{
    // destroying current widget, if any
    this->deleteCurrentWidget();

    QApplication::quit();
}

void MainWindow::onActionMyProfileTriggered(bool checked)
{
    if(m_MyProfileWg == nullptr) {
        this->deleteCurrentWidget();
        m_MyProfileWg = new MyProfileWidget;
        ui->swMain->addWidget(m_MyProfileWg);
        this->setWindowTitle("My Profile");
        connect(m_MyProfileWg, SIGNAL(busy(QString)), this, SLOT(onWidgetBusy(QString)));
        connect(m_MyProfileWg, SIGNAL(ready(QString)), this, SLOT(onWidgetReady(QString)));
    }
}

void MainWindow::onActionPreferenceTriggered(bool checked)
{
    if(m_PreferenceWg == nullptr) {
        this->deleteCurrentWidget();
        m_PreferenceWg = new PreferenceWidget;
        ui->swMain->addWidget(m_PreferenceWg);
        this->setWindowTitle("Preference");
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
    connect(ui->actionPreference, SIGNAL(triggered(bool)), this, SLOT(onActionPreferenceTriggered(bool)));
}

void MainWindow::loadProfile()
{
    m_ApiHandler.setParent(this);
    m_ApiHandler.setMDomain(Constants::DEFAULT_DOMAIN);
    m_ApiHandler.setMModel(Constants::ApiModel::App);
    m_ApiHandler.setMAction(Constants::ApiAction::Profile);
    m_ApiHandler.Execute(ApiHandler::RequestMethod::GET, SLOT(onFetchProfile(QNetworkReply*)));
}

void MainWindow::deleteCurrentWidget()
{
    QWidget* currentWidget = ui->swMain->currentWidget();
    if(currentWidget != nullptr) {
        ui->swMain->removeWidget(currentWidget);
        delete currentWidget;
        currentWidget = nullptr;
    }

    if(m_MyProfileWg != nullptr) {
        m_MyProfileWg = nullptr;
    }
    if(m_PreferenceWg != nullptr) {
        m_PreferenceWg = nullptr;
    }
}
