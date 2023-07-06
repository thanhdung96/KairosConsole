#include "Holiday/HolidayForm.h"
#include "ui_HolidayForm.h"
#include <vector>
#include <QEventLoop>
#include "Dto/Management/HolidayDto.h"
#include "Network/Helper/BaseResponse.h"
#include "Network/Constants/ApiConstants.h"
#include "Network/Helper/json.hpp"

using std::vector;
using DTO::Management::HolidayDto;
using Network::Helper::BaseResponse;
using json = nlohmann::json;

typedef vector<json> LstHolidayDtos;

HolidayForm::HolidayForm(QWidget *parent, const string& holidayId) :
    QWidget(parent),
    ui(new Ui::HolidayForm)
{
    ui->setupUi(this);
    this->initialiseUi();
    m_ApiHandler.setParent(this);
    m_ApiHandler.setMDomain(Network::Constants::DEFAULT_DOMAIN);
    m_ApiHandler.setMModel(Network::Constants::ApiModel::Holiday);

    // if id is empty, it means the New Holiday button was clicked
    // else, the edit button was clicked.

    if(!holidayId.empty()) {
        m_HolidayId = holidayId;
        this->loadHolidayDetail(m_HolidayId);
        ui->lblTitle->setText("Edit Holiday");
    } else {
        ui->lblTitle->setText("New Holiday");
    }
}

HolidayForm::~HolidayForm()
{
    delete ui;
}

void HolidayForm::onFetchHolidayDetail(QNetworkReply *reply)
{
    QEventLoop eventLoop;
    connect(reply, SIGNAL(finished()), &eventLoop, SLOT(quit()));
    BaseResponse response(reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt(),
                          QString(reply->readAll()).toStdString());
    reply->deleteLater();
    HolidayDto holidayDto;
    holidayDto.FromJson(response.getResponseData());

    ui->txtName->setText(QString::fromStdString(holidayDto.getName()));
    ui->deStartDate->setDate(
        QDate::fromString(QString::fromStdString(holidayDto.getStartDate()), "yyyy-MM-dd")
    );
    ui->deEndDate->setDate(
        QDate::fromString(QString::fromStdString(holidayDto.getEndDate()), "yyyy-MM-dd")
    );
    ui->txtYear->setText(QString::number(holidayDto.getYear()));
    ui->cbxIsActive->setChecked(holidayDto.isActive());
    ui->cbxRecurrent->setChecked(holidayDto.isRecurrence());

    this->setBusy(false, "Ready");
}

void HolidayForm::onBtnReturnClicked()
{
    emit HolidayFormReturned(false, "Canceled");
}

void HolidayForm::onBtnSaveClicked()
{
    this->setBusy(true, QString::fromStdString("Saving holiday"));

    HolidayDto holidayDto;
    holidayDto.setName(ui->txtName->text().toStdString());
    holidayDto.setStartDate(ui->deStartDate->date().toString("yyyy-MM-dd").toStdString());
    holidayDto.setEndDate(ui->deEndDate->date().toString("yyyy-MM-dd").toStdString());
    holidayDto.setYear(ui->txtYear->text().toInt());
    holidayDto.setRecurrence(ui->cbxRecurrent->isChecked());

    m_ApiHandler.setMAction(Network::Constants::BLANK);
    if(m_HolidayId.empty()) {
        holidayDto.setActive(true);
        LstHolidayDtos lstHolidayDtos;
        lstHolidayDtos.emplace_back(holidayDto.ToJson(false));
        json submitData;
        submitData["data"] = lstHolidayDtos;

        m_ApiHandler.setRequestBody(submitData.dump());
        m_ApiHandler.Execute(ApiHandler::RequestMethod::POST, SLOT(onHolidaySaved(QNetworkReply*)));
    } else {
        holidayDto.setActive(ui->cbxIsActive->isChecked());

        m_ApiHandler.pushQuery(m_HolidayId);
        m_ApiHandler.setRequestBody(holidayDto.ToJson(true).dump());
        m_ApiHandler.Execute(ApiHandler::RequestMethod::PATCH, SLOT(onHolidaySaved(QNetworkReply*)));
    }
}

void HolidayForm::onHolidaySaved(QNetworkReply *reply)
{
    QEventLoop eventLoop;
    connect(reply, SIGNAL(finished()), &eventLoop, SLOT(quit()));
    BaseResponse response(reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt(),
                          QString(reply->readAll()).toStdString());
    reply->deleteLater();

    if(
        response.ResponseCode() == BaseResponse::Status::HTTP_CREATED ||
        response.ResponseCode() == BaseResponse::Status::HTTP_OK
    ) {
        emit HolidayFormReturned(true, "Holiday saved.");
    } else {
        this->setBusy(false, QString::fromStdString(response.getResponseData()["message"]));
    }
}

void HolidayForm::initialiseUi()
{
    connect(ui->btnSave, SIGNAL(clicked()), this, SLOT(onBtnSaveClicked()));
    connect(ui->btnReturn, SIGNAL(clicked()), this, SLOT(onBtnReturnClicked()));
}

void HolidayForm::loadHolidayDetail(const string &holidayId)
{
    this->setBusy(true, "Loading holiday detail...");
    m_ApiHandler.pushQuery(holidayId);
    m_ApiHandler.Execute(
        ApiHandler::RequestMethod::GET,
        SLOT(onFetchHolidayDetail(QNetworkReply *))
    );
}

void HolidayForm::setBusy(bool isBusy, QString message)
{
    ui->btnSave->setDisabled(isBusy);
    ui->btnReturn->setDisabled(isBusy);

    if(isBusy) {
        emit HolidayFormBusy(message.toStdString());
    } else {
        emit HolidayFormReady(message.toStdString());
    }
}
