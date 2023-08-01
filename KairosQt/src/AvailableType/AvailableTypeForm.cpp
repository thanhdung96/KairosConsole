#include "AvailableType/AvailableTypeForm.h"
#include "ui_AvailableTypeForm.h"
#include <QEventLoop>
#include "Dto/Management/AvailableTypeDto.h"
#include "Network/Constants/ApiConstants.h"
#include "Network/Helper/BaseResponse.h"

using Network::Helper::BaseResponse;
using DTO::Management::AvailableTypeDto;

AvailableTypeForm::AvailableTypeForm(QWidget *parent, const string& typeId) :
    QWidget(parent),
    ui(new Ui::AvailableTypeForm)
{
    ui->setupUi(this);
    this->initialiseUi();
    m_ApiHandler.setParent(this);
    m_ApiHandler.setMModel(Network::Constants::ApiModel::LeaveType);
    m_ApiHandler.setMDomain(Network::Constants::DEFAULT_DOMAIN);

    m_TypeId = typeId;
    if(!m_TypeId.empty()) {
        ui->lblTitle->setText("Edit Available Type");
        this->loadTypeDetail();
    } else {
        ui->lblTitle->setText("Create Available Type");
    }
}

AvailableTypeForm::~AvailableTypeForm()
{
    delete ui;
}

void AvailableTypeForm::onFetchTypeDetail(QNetworkReply *reply)
{
    QEventLoop eventLoop;
    connect(reply, SIGNAL(finished()), &eventLoop, SLOT(quit()));
    BaseResponse response(reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt(),
                          QString(reply->readAll()).toStdString());
    reply->deleteLater();
    AvailableTypeDto typeDto;
    typeDto.FromJson(response.getResponseData());

    ui->txtName->setText(QString::fromStdString(typeDto.getName()));
    ui->txtDescription->setText(QString::fromStdString(typeDto.getDescription()));
    ui->txtFileDescription->setText(QString::fromStdString(typeDto.getDescriptionRequiredFiles()));
    ui->spMaxDuration->setValue(typeDto.getMaximumDay());
    ui->cbxLeaveToll->setChecked(typeDto.isLeaveToll());
    ui->cbxRequireFile->setChecked(typeDto.isRequireFile());
    ui->cbxUnpaid->setChecked(typeDto.isUnpaid());
    ui->cbxActive->setChecked(typeDto.isActive());

    this->setBusy(false, "Ready");
}

void AvailableTypeForm::onBtnSaveClicked()
{
    this->setBusy(true, QString::fromStdString("Saving Leave Type"));

    AvailableTypeDto typeDto;
    typeDto.setName(ui->txtName->text().toStdString());
    typeDto.setDescription(ui->txtDescription->text().toStdString());
    typeDto.setDescriptionRequiredFiles(ui->txtFileDescription->text().toStdString());
    typeDto.setMaximumDay(ui->spMaxDuration->value());
    typeDto.setLeaveToll(ui->cbxLeaveToll->isChecked());
    typeDto.setRequireFile(ui->cbxRequireFile->isChecked());
    typeDto.setUnpaid(ui->cbxUnpaid->isChecked());
    typeDto.setActive(true);

    m_ApiHandler.setMAction(Network::Constants::BLANK);
    if(m_TypeId.empty()) {
        m_ApiHandler.setRequestBody(typeDto.ToJson(true).dump());
        m_ApiHandler.Execute(ApiHandler::RequestMethod::POST, SLOT(onAvailableTypeSaved(QNetworkReply*)));
    } else {
        typeDto.setActive(ui->cbxActive->isChecked());
        m_ApiHandler.pushQuery(m_TypeId);
        m_ApiHandler.setRequestBody(typeDto.ToJson(true).dump());
        m_ApiHandler.Execute(ApiHandler::RequestMethod::PATCH, SLOT(onAvailableTypeSaved(QNetworkReply*)));
    }
}

void AvailableTypeForm::onBtnReturnClicked()
{
    emit TypeFormReturned(false, "Canceled");
}

void AvailableTypeForm::onAvailableTypeSaved(QNetworkReply *reply)
{
    QEventLoop eventLoop;
    connect(reply, SIGNAL(finished()), &eventLoop, SLOT(quit()));
    BaseResponse response(reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt(),
                          QString(reply->readAll()).toStdString());
    reply->deleteLater();

    if(
        response.ResponseCode() == BaseResponse::Status::HTTP_OK ||
        response.ResponseCode() == BaseResponse::Status::HTTP_CREATED
    ) {
        emit TypeFormReturned(true, "Available Type saved.");
    } else {
        this->setBusy(false, QString::fromStdString(response.GetRawResponse()));
    }
}

void AvailableTypeForm::loadTypeDetail()
{
    this->setBusy(true, "Fetching Available Type Detail");

    m_ApiHandler.pushQuery(m_TypeId);
    m_ApiHandler.Execute(
        ApiHandler::RequestMethod::GET,
        SLOT(onFetchTypeDetail(QNetworkReply *))
    );
}

void AvailableTypeForm::initialiseUi()
{
    connect(ui->btnSave, SIGNAL(clicked()), this, SLOT(onBtnSaveClicked()));
    connect(ui->btnReturn, SIGNAL(clicked()), this, SLOT(onBtnReturnClicked()));
}

void AvailableTypeForm::setBusy(bool isBusy, QString message)
{
    ui->btnSave->setDisabled(isBusy);
    ui->btnReturn->setDisabled(isBusy);

    if(isBusy) {
        emit TypeFormBusy(message.toStdString());
    } else {
        emit TypeFormReady(message.toStdString());
    }
}
