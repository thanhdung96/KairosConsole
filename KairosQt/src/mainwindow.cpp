#include "mainwindow.h"
#include "Security/logindialog.h"
#include "ui_mainwindow.h"
#include <QPushButton>
#include <QEventLoop>
#include <QAction>
#include <QApplication>
#include "Network/Helper/BaseResponse.h"
#include "Network/ApiHandler.h"
#include "Network/Constants/ApiConstants.h"
#include "App/Session.h"
#include "App/UserRole.h"

using Network::Helper::BaseResponse;

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
        m_MyProfileWg->deleteLater();
    }
    if(m_PreferenceWg != nullptr) {
        m_PreferenceWg->deleteLater();
    }
    if(m_RoleListingWg != nullptr) {
        m_RoleListingWg->deleteLater();
    }
    if(m_TypeListingWidget != nullptr) {
        m_TypeListingWidget->deleteLater();
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
    App::Session::setRole(
        App::UserRole::resolveCode(response.getResponseData()["account"]["role"])
    );
}

void MainWindow::onActionQuitTriggered(bool checked)
{
    // destroying current widget, if any
    this->deleteCurrentWidget();
    m_LstSideBtns.clear();

    QApplication::quit();
}

void MainWindow::onActionMyProfileTriggered(bool checked)
{
    if(m_MyProfileWg == nullptr) {
        this->deleteCurrentWidget();
        m_MyProfileWg = new MyProfileWidget(this);
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
        m_PreferenceWg = new PreferenceWidget(this);
        ui->swMain->addWidget(m_PreferenceWg);
        this->setWindowTitle("Preference");
        connect(m_PreferenceWg, SIGNAL(busy(QString)), this, SLOT(onWidgetBusy(QString)));
        connect(m_PreferenceWg, SIGNAL(ready(QString)), this, SLOT(onWidgetReady(QString)));
    }
}

void MainWindow::onBtnSideTitleClicked()
{
    if(m_RoleListingWg == nullptr) {
        this->deleteCurrentWidget();
        this->checkListSideButtons(ui->btnSideTitles);
        m_RoleListingWg = new RoleListingWidget(this);
        ui->swMain->addWidget(m_RoleListingWg);
        this->setWindowTitle("Roles");
        connect(m_RoleListingWg, SIGNAL(busy(QString)), this, SLOT(onWidgetBusy(QString)));
        connect(m_RoleListingWg, SIGNAL(ready(QString)), this, SLOT(onWidgetReady(QString)));
    }
}

void MainWindow::onBtnSideHolidaysClicked()
{
    this->checkListSideButtons(ui->btnSideHolidays);
}

void MainWindow::onBtnSideLeaveTypesClicked()
{
    if(m_TypeListingWidget == nullptr) {
        this->deleteCurrentWidget();
        this->checkListSideButtons(ui->btnSideLeaveTypes);
        m_TypeListingWidget = new AvailableTypeListingWidget(this);
        ui->swMain->addWidget(m_TypeListingWidget);
        this->setWindowTitle("Roles");
        connect(m_TypeListingWidget, SIGNAL(busy(QString)), this, SLOT(onWidgetBusy(QString)));
        connect(m_TypeListingWidget, SIGNAL(ready(QString)), this, SLOT(onWidgetReady(QString)));
    }
}

void MainWindow::onBtnSideEmployeesClicked()
{
    this->checkListSideButtons(ui->btnSideEmployees);
}

void MainWindow::onBtnSideImportClicked()
{
    this->checkListSideButtons(ui->btnSideImport);
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
    connect(ui->btnSideTitles, SIGNAL(clicked()), this, SLOT(onBtnSideTitleClicked()));
    connect(ui->btnSideHolidays, SIGNAL(clicked()), this, SLOT(onBtnSideHolidaysClicked()));
    connect(ui->btnSideLeaveTypes, SIGNAL(clicked()), this, SLOT(onBtnSideLeaveTypesClicked()));
    connect(ui->btnSideEmployees, SIGNAL(clicked()), this, SLOT(onBtnSideEmployeesClicked()));
    connect(ui->btnSideImport, SIGNAL(clicked()), this, SLOT(onBtnSideImportClicked()));

    m_LstSideBtns.emplace_back(ui->btnSideTitles);
    m_LstSideBtns.emplace_back(ui->btnSideEmployees);
    m_LstSideBtns.emplace_back(ui->btnSideHolidays);
    m_LstSideBtns.emplace_back(ui->btnSideLeaveTypes);
    m_LstSideBtns.emplace_back(ui->btnSideImport);
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
    if(m_RoleListingWg != nullptr) {
        m_RoleListingWg = nullptr;
    }
    if(m_TypeListingWidget != nullptr) {
        m_TypeListingWidget = nullptr;
    }
}

void MainWindow::checkListSideButtons(QPushButton* selectedSideBtn)
{
    for(size_t i = 0; i < m_LstSideBtns.size(); i += 1) {
        m_LstSideBtns[i]->setChecked(false);
    }
    selectedSideBtn->setChecked(true);
}
