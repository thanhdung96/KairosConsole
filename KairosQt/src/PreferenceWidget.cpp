#include "PreferenceWidget.h"
#include <QEventLoop>
#include <QMessageBox>
#include <string>
#include "Dto/App/SettingDto.h"
#include "Dto/Security/ChangePasswordDto.h"
#include "Network/Constants/ApiConstants.h"
#include "Network/Helper/BaseResponse.h"
#include "ui_PreferenceWidget.h"
using namespace DTO::App;
using namespace DTO::Security;

PreferenceWidget::PreferenceWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PreferenceWidget)
{
    ui->setupUi(this);
    m_ApiHandler.setParent(this);
    m_ApiHandler.setMDomain(Constants::DEFAULT_DOMAIN);

    this->initialiseUi();
    this->loadPreference();
}

PreferenceWidget::~PreferenceWidget()
{
    delete ui;
}

void PreferenceWidget::initialiseUi()
{
    connect(ui->btnSaveSetting, SIGNAL(clicked()), this, SLOT(onBtnSaveSettingClicked()));
    connect(ui->btnSavePassword, SIGNAL(clicked()), this, SLOT(onBtnSavePasswordClicked()));

    m_LstSupportedLanguages = DisplayLanguage::getAllLanguages();
    foreach (std::string language, m_LstSupportedLanguages) {
        ui->drdDisplayLanguage->addItem(QString::fromStdString(language));
    }
}

void PreferenceWidget::loadPreference()
{
    this->setBusy(true, "Loading preference...");

    m_ApiHandler.setMModel(Constants::ApiModel::App);
    m_ApiHandler.setMAction(Constants::ApiAction::ProfileSetting);
    m_ApiHandler.Execute(ApiHandler::RequestMethod::GET, SLOT(onFetchPreference(QNetworkReply *)));
}

void PreferenceWidget::onFetchPreference(QNetworkReply *reply)
{
    QEventLoop eventLoop;
    connect(reply, SIGNAL(finished()), &eventLoop, SLOT(quit()));
    BaseResponse response(reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt(),
                          QString(reply->readAll()).toStdString());
    reply->deleteLater();

    SettingDto settingDto;
    settingDto.FromJson(response.getResponseData());

    ui->cbxDailySummary->setChecked(settingDto.getDailySummary());
    ui->cbxWeeklySummary->setChecked(settingDto.getWeeklySummary());
    ui->cbxMonthlySummary->setChecked(settingDto.getMonthlySummary());
    ui->drdDisplayLanguage->setCurrentText(
        QString::fromStdString(
            DisplayLanguage::resolve(
                settingDto.getDisplayLanguage(),
                DisplayLanguage::ResolveType::FromCode
            )
    ));

    this->setBusy(false, "Ready");
}

void PreferenceWidget::onBtnSavePasswordClicked() {
    this->setBusy(true, "Changing password...");
    ChangePasswordDto changePasswordDto;
    changePasswordDto.setNewPassword(ui->txtNewPassword->text().toStdString());
    changePasswordDto.setOldPassword(ui->txtOldPassword->text().toStdString());

    QMessageBox messageBox;
    messageBox.setText("You are about to change your password");
    messageBox.setInformativeText("KairosQt will automatically close for your account to be fully updated.");
    messageBox.setStandardButtons(QMessageBox::StandardButton::Ok | QMessageBox::StandardButton::Cancel);
    messageBox.setDefaultButton(QMessageBox::StandardButton::Ok);
    int ret = messageBox.exec();

    if(ret == QMessageBox::Ok) {
        m_ApiHandler.setMModel(Constants::ApiModel::Security);
        m_ApiHandler.setMAction(Constants::ApiAction::Change);
        m_ApiHandler.setRequestBody(changePasswordDto.ToJson(false).dump());
        m_ApiHandler.Execute(ApiHandler::RequestMethod::PATCH, SLOT(onPasswordChanged(QNetworkReply *)));
    } else {
        this->setBusy(false, "Changing password canceled.");
    }
}

void PreferenceWidget::onBtnSaveSettingClicked() {
    this->setBusy(true, "Saving preferences...");
    SettingDto settingDto;
    settingDto.setDailySummary(ui->cbxDailySummary->isChecked());
    settingDto.setWeeklySummary(ui->cbxWeeklySummary->isChecked());
    settingDto.setMonthlySummary(ui->cbxMonthlySummary->isChecked());
    settingDto.setDisplayLanguage(
        DisplayLanguage::resolve(
            ui->drdDisplayLanguage->currentText().toStdString(),
            DisplayLanguage::ResolveType::ToCode
            )
        );

    m_ApiHandler.setMModel(Constants::ApiModel::App);
    m_ApiHandler.setMAction(Constants::ApiAction::ProfileSetting);
    m_ApiHandler.setRequestBody(settingDto.ToJson(true).dump());
    m_ApiHandler.Execute(ApiHandler::RequestMethod::PATCH, SLOT(onSettingSaved(QNetworkReply *)));
}

void PreferenceWidget::onSettingSaved(QNetworkReply *reply)
{
    QEventLoop eventLoop;
    connect(reply, SIGNAL(finished()), &eventLoop, SLOT(quit()));
    BaseResponse response(reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt(),
                          QString(reply->readAll()).toStdString());
    reply->deleteLater();

    this->setBusy(false, QString::fromStdString(response.getResponseData()["message"]));
}

void PreferenceWidget::onPasswordChanged(QNetworkReply *reply)
{
    QEventLoop eventLoop;
    connect(reply, SIGNAL(finished()), &eventLoop, SLOT(quit()));
    BaseResponse response(reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt(),
                          QString(reply->readAll()).toStdString());
    reply->deleteLater();

    if(response.ResponseCode() != BaseResponse::Status::HTTP_OK) {
        this->setBusy(false, QString::fromStdString(response.getResponseData()["message"]));
    } else {
        this->setBusy(false, "Ready");
        QMessageBox messageBox;
        messageBox.setText("Password updated.");
        messageBox.setStandardButtons(QMessageBox::StandardButton::Ok);
        messageBox.setDefaultButton(QMessageBox::StandardButton::Ok);
        messageBox.exec();

        QApplication::quit();
    }
}

void PreferenceWidget::setBusy(bool isBusy, QString message)
{
    ui->btnSaveSetting->setDisabled(isBusy);
    ui->btnSavePassword->setDisabled(isBusy);

    if (isBusy) {
        emit busy(message);
    } else {
        emit ready(message);
    }
}
