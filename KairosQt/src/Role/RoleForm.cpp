#include "Role/RoleForm.h"
#include "ui_RoleForm.h"
#include <QEventLoop>
#include "Network/Constants/ApiConstants.h"
#include "Network/Helper/BaseResponse.h"
#include "Dto/Management/RoleDto.h"
#include "App/UserRole.h"

using DTO::Management::RoleDto;
using Network::Helper::BaseResponse;

RoleForm::RoleForm(QWidget *parent, const string& roleId) :
    QWidget(parent),
    ui(new Ui::RoleForm)
{
    ui->setupUi(this);
    this->initialiseUi();
    m_ApiHandler.setParent(this);
    m_ApiHandler.setMDomain(Constants::DEFAULT_DOMAIN);

    // if role id is empty, it means the New Role button was clicked
    // else, the edit button was clicked.
    m_RoleId = roleId;
    if(!m_RoleId.empty()) {
        this->loadRoleDetail(m_RoleId);
        ui->lblTitle->setText("Edit Title");
    } else {
        ui->lblTitle->setText("New Title");
    }
}

RoleForm::~RoleForm()
{
    delete ui;
}

void RoleForm::onFetchRoleDetail(QNetworkReply *reply)
{
    QEventLoop eventLoop;
    connect(reply, SIGNAL(finished()), &eventLoop, SLOT(quit()));
    BaseResponse response(reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt(),
                          QString(reply->readAll()).toStdString());
    reply->deleteLater();
    RoleDto roleDto;
    roleDto.FromJson(response.getResponseData());

    ui->txtRoleName->setText(QString::fromStdString(roleDto.getName()));
    ui->txtDescription->setText(QString::fromStdString(roleDto.getDescription()));
    ui->dsbMaxDuration->setValue(roleDto.getMaxLeaveBalance());
    ui->drdCode->setCurrentText(
        QString::fromStdString(
            App::UserRole::getNameFromCode(roleDto.getCode())
        )
    );

    this->setBusy(false, "Ready");
}

void RoleForm::onBtnReturnClicked()
{
    emit RoleFormReturned(false, "Canceled");
}

void RoleForm::onBtnSaveClicked()
{
    this->setBusy(true, QString::fromStdString("Saving employee role"));

    RoleDto roleDto;
    roleDto.setName(ui->txtRoleName->text().toStdString());
    roleDto.setDescription(ui->txtDescription->text().toStdString());
    roleDto.setMaxLeaveBalance(ui->dsbMaxDuration->value());
    roleDto.setCode(
        App::UserRole::resolveName(
            ui->drdCode->currentText().toStdString()
        )
    );
    roleDto.setActive(true);

    m_ApiHandler.setMModel(Constants::ApiModel::Role);
    m_ApiHandler.setMAction("");
    if(m_RoleId.empty()) {
        m_ApiHandler.setRequestBody(roleDto.ToJson(true).dump());
        m_ApiHandler.Execute(ApiHandler::RequestMethod::POST, SLOT(onRoleSaved(QNetworkReply*)));
    } else {
        roleDto.setActive(ui->cbxActive->isChecked());

        m_ApiHandler.pushQuery(m_RoleId);
        m_ApiHandler.setRequestBody(roleDto.ToJson(true).dump());
        m_ApiHandler.Execute(ApiHandler::RequestMethod::PATCH, SLOT(onRoleSaved(QNetworkReply*)));
    }
}

void RoleForm::onRoleSaved(QNetworkReply *reply)
{
    QEventLoop eventLoop;
    connect(reply, SIGNAL(finished()), &eventLoop, SLOT(quit()));
    BaseResponse response(reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt(),
                          QString(reply->readAll()).toStdString());
    reply->deleteLater();

    if(response.ResponseCode() == BaseResponse::Status::HTTP_OK) {
        emit RoleFormReturned(true, "Employee role saved.");
    } else {
        this->setBusy(false, QString::fromStdString(response.GetRawResponse()));
    }
}

void RoleForm::initialiseUi()
{
    connect(ui->btnReturn, SIGNAL(clicked()), this, SLOT(onBtnReturnClicked()));
    connect(ui->btnSave, SIGNAL(clicked()), this, SLOT(onBtnSaveClicked()));
}

void RoleForm::loadRoleDetail(const string &roleId)
{
    this->setBusy(true, "Fetching role detail");

    m_ApiHandler.setMModel(Constants::ApiModel::Role);
    m_ApiHandler.pushQuery(roleId);
    m_ApiHandler.Execute(
        ApiHandler::RequestMethod::GET,
        SLOT(onFetchRoleDetail(QNetworkReply *))
    );
}

void RoleForm::setBusy(bool isBusy, QString message)
{
    ui->btnSave->setDisabled(isBusy);
    ui->btnReturn->setDisabled(isBusy);

    if(isBusy) {
        emit RoleFormBusy(message.toStdString());
    } else {
        emit RoleFormReady(message.toStdString());
    }
}
