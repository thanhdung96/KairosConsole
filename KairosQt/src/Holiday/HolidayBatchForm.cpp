#include "Holiday/HolidayBatchForm.h"
#include "ui_HolidayBatchForm.h"
#include <QEventLoop>
#include <QObjectList>
#include "Network/Constants/ApiConstants.h"
#include "Network/Helper/BaseResponse.h"
#include "App/CountryCode.h"
#include "Dto/Management/HolidayDto.h"
#include "Network/Helper/json.hpp"

using App::CountryCode;
using DTO::Management::HolidayDto;
using Network::Helper::BaseResponse;
using json = nlohmann::json;

typedef vector<json> LstHolidayDtos;

HolidayBatchForm::HolidayBatchForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HolidayBatchForm)
{
    ui->setupUi(this);

    m_ApiHandler.setParent(this);
    m_ApiHandler.setMDomain(Network::Constants::DEFAULT_DOMAIN);

    this->initialiseUi();
    this->generateSamples();
}

HolidayBatchForm::~HolidayBatchForm()
{
    foreach (HolidayRowForm* rowForm, m_LstHolidayRows) {
        rowForm->deleteLater();
    }
    delete ui;
}

void HolidayBatchForm::onBtnSaveClicked()
{
    LstHolidayDtos lstHolidayDtos;
    foreach (HolidayRowForm* rowForm, m_LstHolidayRows) {
        lstHolidayDtos.emplace_back(rowForm->getData());
    }

    json submitData;
    submitData["data"] = lstHolidayDtos;

    this->setBusy(true, "Saving holidays...");
    m_ApiHandler.setMAction(Network::Constants::BLANK);
    m_ApiHandler.clearQuery();
    m_ApiHandler.setRequestBody(submitData.dump());
    m_ApiHandler.Execute(ApiHandler::RequestMethod::POST, SLOT(onHolidaysSaved(QNetworkReply*)));
}

void HolidayBatchForm::onBtnReturnClicked()
{
    emit HolidayFormReturned(false, "Canceled");
}

void HolidayBatchForm::onFetchSamples(QNetworkReply *reply)
{
    QEventLoop eventLoop;
    connect(reply, SIGNAL(finished()), &eventLoop, SLOT(quit()));
    BaseResponse response(reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt(),
                          QString(reply->readAll()).toStdString());
    reply->deleteLater();

    json lstHolidayDto = response.getResponseData();
    for(size_t i = 0; i < lstHolidayDto.size(); i += 1) {
        HolidayDto holidayDto;
        holidayDto.FromJson(lstHolidayDto[i]);

        HolidayRowForm* rowForm = new HolidayRowForm(this, &holidayDto);
        this->connectRowForm(rowForm);
        rowForm->setId(i);

        m_LstHolidayRows.push_back(rowForm);
        ui->scrLayout->layout()->addWidget(rowForm);
    }
    this->reassignIdToRowForms();

    this->setBusy(false, "Ready");
}

void HolidayBatchForm::onHolidaysSaved(QNetworkReply *reply)
{
    QEventLoop eventLoop;
    connect(reply, SIGNAL(finished()), &eventLoop, SLOT(quit()));
    BaseResponse response(reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt(),
                          QString(reply->readAll()).toStdString());
    reply->deleteLater();

    if(response.ResponseCode() == BaseResponse::Status::HTTP_CREATED) {
        emit HolidayFormReturned(true, "Holidays saved.");
    } else {
        this->setBusy(false, QString::fromStdString(response.getResponseData()["message"]));
    }
}

void HolidayBatchForm::onRowFormDeleted(size_t id)
{
    HolidayRowForm* rowToDelete = m_LstHolidayRows.at(id);
    m_LstHolidayRows.erase(m_LstHolidayRows.begin() + id);
    rowToDelete->deleteLater();

    this->reassignIdToRowForms();
}

void HolidayBatchForm::onRowFormSelected(size_t id)
{
    // if none is selected yet
    if(m_SelectedRow == nullptr) {
        m_SelectedRow = m_LstHolidayRows.at(id);
        m_SelectedRow->setSelected(true);
    } else {
        m_SelectedRow->setSelected(false);
        // if another row is selected
        if(m_SelectedRow->getId() != m_LstHolidayRows.at(id)->getId()) {
            m_SelectedRow = m_LstHolidayRows.at(id);
            m_SelectedRow->setSelected(true);
        } else {
            // if deselected
            m_SelectedRow = nullptr;
        }
    }

    // only show row functions when a row is selected
    if(m_SelectedRow == nullptr) {
        ui->wgRowFunc->hide();
    } else {
        ui->wgRowFunc->show();
    }
}

void HolidayBatchForm::onBtnNewClicked()
{
    HolidayDto holidayDto;
    HolidayRowForm* rowForm = new HolidayRowForm(this, &holidayDto);
    this->connectRowForm(rowForm);

    m_LstHolidayRows.push_back(rowForm);
    ui->scrLayout->layout()->addWidget(rowForm);

    this->reassignIdToRowForms();
}

void HolidayBatchForm::onBtnUpClicked()
{
    // only item not at the first position can be moved upward
    if(m_SelectedRow->getId() > 0) {
        // clear row forms in the layout
        foreach (HolidayRowForm* rowForm, m_LstHolidayRows) {
            rowForm->setParent(nullptr);
        }

        // rearrange items in the list
        m_LstHolidayRows.erase(m_LstHolidayRows.begin() + m_SelectedRow->getId());
        m_LstHolidayRows.insert(m_LstHolidayRows.begin() + m_SelectedRow->getId() - 1, m_SelectedRow);
        this->reassignIdToRowForms();

        // add items in the list back to the layout again
        foreach (HolidayRowForm* rowForm, m_LstHolidayRows) {
            ui->scrLayout->layout()->addWidget(rowForm);
        }
    }
}

void HolidayBatchForm::onBtnDownClicked()
{
    // only item not at the last position can be moved downward
    if(m_SelectedRow->getId() < m_LstHolidayRows.size() - 1) {
        // clear row forms in the layout
        foreach (HolidayRowForm* rowForm, m_LstHolidayRows) {
            rowForm->setParent(nullptr);
        }

        // rearrange items in the list
        m_LstHolidayRows.erase(m_LstHolidayRows.begin() + m_SelectedRow->getId());
        m_LstHolidayRows.insert(m_LstHolidayRows.begin() + m_SelectedRow->getId() + 1, m_SelectedRow);
        this->reassignIdToRowForms();

        // add items in the list back to the layout again
        foreach (HolidayRowForm* rowForm, m_LstHolidayRows) {
            ui->scrLayout->layout()->addWidget(rowForm);
        }
    }
}

void HolidayBatchForm::setBusy(bool isBusy, QString message)
{
    ui->btnSave->setDisabled(isBusy);
    ui->btnReturn->setDisabled(isBusy);

    if (isBusy) {
        emit busy(message);
    } else {
        emit ready(message);
    }
}

void HolidayBatchForm::initialiseUi()
{
    ui->wgRowFunc->hide();

    connect(ui->btnReturn, SIGNAL(clicked()), this, SLOT(onBtnReturnClicked()));
    connect(ui->btnSave, SIGNAL(clicked()), this, SLOT(onBtnSaveClicked()));
    connect(ui->btnNew, SIGNAL(clicked()), this, SLOT(onBtnNewClicked()));
    connect(ui->btnUp, SIGNAL(clicked()), this, SLOT(onBtnUpClicked()));
    connect(ui->btnDown, SIGNAL(clicked()), this, SLOT(onBtnDownClicked()));
}

void HolidayBatchForm::generateSamples()
{
    this->setBusy(true, "Generating sample holidays...");
    m_ApiHandler.setMModel(Network::Constants::ApiModel::Holiday);
    m_ApiHandler.setMAction(Network::Constants::ApiAction::Batch);
    m_ApiHandler.pushQuery(CountryCode::Vietnam);
    m_ApiHandler.Execute(ApiHandler::RequestMethod::GET, SLOT(onFetchSamples(QNetworkReply*)));
}

void HolidayBatchForm::reassignIdToRowForms()
{
    size_t numberOrder = 0;
    foreach (HolidayRowForm* rowForm, m_LstHolidayRows) {
        rowForm->setId(numberOrder);
        numberOrder += 1;
    }
}

void HolidayBatchForm::connectRowForm(HolidayRowForm *rowForm)
{
    connect(
        rowForm,
        SIGNAL(deleted(size_t)),
        this,
        SLOT(onRowFormDeleted(size_t))
    );

    connect(
        rowForm,
        SIGNAL(selected(size_t)),
        this,
        SLOT(onRowFormSelected(size_t))
    );
}
