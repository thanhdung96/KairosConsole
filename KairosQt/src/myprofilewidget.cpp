#include "myprofilewidget.h"
#include "ui_myprofilewidget.h"
#include "Network/Constants/ApiConstants.h"
#include "Network/Helper/BaseResponse.h"
#include "App/Displaylanguage.h"
#include "App/UserStatus.h"
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QString>

using json = nlohmann::json;
using namespace App;

MyProfileWidget::MyProfileWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MyProfileWidget)
{
    ui->setupUi(this);

    this->loadProfile();
    this->initialiseUi();
}

MyProfileWidget::~MyProfileWidget()
{
    delete ui;
}

void MyProfileWidget::onFetchProfile(QNetworkReply *reply)
{
    QEventLoop eventLoop;
    connect(reply, SIGNAL(finished()), &eventLoop, SLOT(quit()));
    BaseResponse response(
        reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt(),
        QString(reply->readAll()).toStdString()
    );
    reply->deleteLater();

    if(response.ResponseCode() == BaseResponse::Status::HTTP_OK) {
        m_ProfileDto.fromJson(response.getResponseData());

        // mapping data to text fields
        ui->txtFirstName->setText(QString::fromStdString(m_ProfileDto.getFirstName()));
        ui->txtLastName->setText(QString::fromStdString(m_ProfileDto.getLastName()));
        ui->txtStatus->setText(QString::fromStdString(
                                    App::UserStatus::resolveFromCode(
                                        m_ProfileDto.getStatus()
                                    )
        ));
        ui->txtDOB->setText(QString::fromStdString(m_ProfileDto.getDob()));
        ui->txtMotorBrand->setText(QString::fromStdString(m_ProfileDto.getMotoBrand()));
        ui->txtPlateNumber->setText(QString::fromStdString(m_ProfileDto.getPlateNumber()));
        ui->txtPhoneNumber->setText(QString::fromStdString(m_ProfileDto.getPhoneNumber()));
        ui->txtIdNumber->setText(QString::fromStdString(m_ProfileDto.getCitizenId()));
        ui->txtSocialId->setText(QString::fromStdString(m_ProfileDto.getSocialInsurranceId()));
        ui->cbxDisplayLanguage->setCurrentText(QString::fromStdString(
                                    App::DisplayLanguage::resolve(
                                        m_ProfileDto.getDisplayLanguage(),
                                        App::DisplayLanguage::ResolveType::FromCode
                                    )
        ));
        ui->txtPermAddress->setText(QString::fromStdString(m_ProfileDto.getPermanentAddress()));
        ui->txtTempAddress->setText(QString::fromStdString(m_ProfileDto.getTempAddress()));
        ui->txtNationality->setText(QString::fromStdString(m_ProfileDto.getNationality()));
        ui->txtFirstWorkingDate->setText(QString::fromStdString(m_ProfileDto.getFirstWorkingDay()));
        ui->txtEmpCode->setText(QString::fromStdString(m_ProfileDto.getEmpCode()));
        ui->txtEmail->setText(QString::fromStdString(m_ProfileDto.getEmail()));
    }

    this->setBusy(false, "Ready");
}

void MyProfileWidget::onPatchedProfile(QNetworkReply *reply)
{
    QEventLoop eventLoop;
    connect(reply, SIGNAL(finished()), &eventLoop, SLOT(quit()));

    BaseResponse response(
        reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt(),
        QString(reply->readAll()).toStdString()
    );
    reply->deleteLater();

    if(response.ResponseCode() == BaseResponse::Status::HTTP_OK) {
        this->setBusy(false, "Profile saved");
    } else {
        this->setBusy(false, QString::fromStdString(response.getResponseData()["message"]));
    }
}

void MyProfileWidget::onBtnSaveClicked()
{
    ProfileDto profileDto;
    profileDto.setMotoBrand(ui->txtMotorBrand->text().toStdString());
    profileDto.setPlateNumber(ui->txtPlateNumber->text().toStdString());
    profileDto.setPhoneNumber(ui->txtPhoneNumber->text().toStdString());
    profileDto.setCitizenId(ui->txtIdNumber->text().toStdString());
    profileDto.setSocialInsurranceId(ui->txtSocialId->text().toStdString());
    profileDto.setPhoneNumber(ui->txtPhoneNumber->text().toStdString());
    profileDto.setDisplayLanguage(
        App::DisplayLanguage::resolve(
            ui->txtPhoneNumber->text().toStdString(),
            App::DisplayLanguage::ResolveType::ToCode
        )
    );
    profileDto.setPhoneNumber(ui->txtPhoneNumber->text().toStdString());
    profileDto.setPermanentAddress(ui->txtPermAddress->text().toStdString());
    profileDto.setTempAddress(ui->txtTempAddress->text().toStdString());
    profileDto.setPhoneNumber(ui->txtPhoneNumber->text().toStdString());

    this->setBusy(true, "Saving profile...");
    m_ApiHandler.setParent(this);
    m_ApiHandler.setMDomain(Constants::DEFAULT_DOMAIN);
    m_ApiHandler.setMModel(Constants::ApiModel::App);
    m_ApiHandler.setMAction(Constants::ApiAction::Profile);
    m_ApiHandler.setRequestBody(profileDto.toJson(true).dump());
    m_ApiHandler.Execute(ApiHandler::RequestMethod::PATCH, SLOT(onPatchedProfile(QNetworkReply*)));
}

void MyProfileWidget::loadProfile()
{
    this->setBusy(true, "Loading profile...");
    m_ApiHandler.setParent(this);
    m_ApiHandler.setMDomain(Constants::DEFAULT_DOMAIN);
    m_ApiHandler.setMModel(Constants::ApiModel::App);
    m_ApiHandler.setMAction(Constants::ApiAction::Profile);
    m_ApiHandler.Execute(ApiHandler::RequestMethod::GET, SLOT(onFetchProfile(QNetworkReply*)));
}

void MyProfileWidget::initialiseUi()
{
    connect(ui->btnSave, SIGNAL(clicked()), this, SLOT(onBtnSaveClicked()));
}

void MyProfileWidget::setBusy(bool isBusy, QString message)
{
    if(isBusy) {
        emit busy(message);
        ui->btnSave->setEnabled(false);
    } else {
        emit ready(message);
        ui->btnSave->setEnabled(true);
    }
}
