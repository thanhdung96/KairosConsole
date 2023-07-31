#include "Holiday/HolidayListingWidget.h"
#include "ui_HolidayListingWidget.h"
#include <QDate>
#include <QEventLoop>
#include <QMessageBox>
#include "Dto/App/StatusDto.h"
#include "Network/Helper/BaseResponse.h"

using DTO::App::StatusDto;
using Network::Helper::BaseResponse;

HolidayListingWidget::HolidayListingWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HolidayListingWidget)
{
    ui->setupUi(this);

    m_ApiHandler.setParent(this);
    m_ApiHandler.setMModel(Network::Constants::ApiModel::Holiday);
    m_ApiHandler.setMDomain(Network::Constants::DEFAULT_DOMAIN);
    this->initialiseUi();
    this->loadHoliday(Network::Constants::Query::All);
}

HolidayListingWidget::~HolidayListingWidget()
{
    this->m_HolidayModel->deleteLater();
    if(m_HolidayForm != nullptr) {
        m_HolidayForm->deleteLater();
    }
    if(m_HolidayBatchForm != nullptr) {
        m_HolidayBatchForm->deleteLater();
    }
    delete ui;
}

void HolidayListingWidget::setBusy(bool isBusy, QString message)
{
    ui->cbxFilter->setDisabled(isBusy);
    ui->btnEdit->setDisabled(isBusy);
    ui->cbxStatus->setDisabled(isBusy);
    ui->btnBatchNew->setDisabled(isBusy);
    ui->btnNew->setDisabled(isBusy);

    if (isBusy) {
        emit busy(message);
    } else {
        emit ready(message);
    }
}

void HolidayListingWidget::initialiseUi()
{
    connect(
        ui->cbxFilter,
        SIGNAL(currentTextChanged(QString)),
        this,
        SLOT(onCbxFilterTextChanged(QString))
    );
    connect(
        ui->cbxStatus,
        SIGNAL(currentTextChanged(QString)),
        this,
        SLOT(onCbxStatusTextChanged(QString))
    );
    connect(ui->btnBatchNew, SIGNAL(clicked()), this, SLOT(onBtnBatchNewHolidayClicked()));
    connect(ui->btnNew, SIGNAL(clicked()), this, SLOT(onBtnNewHolidayClicked()));
    connect(ui->btnEdit, SIGNAL(clicked()), this, SLOT(onBtnEditClicked()));
}

void HolidayListingWidget::loadHoliday(const string &filter)
{
    this->setBusy(true, "Loading this year\'s holidays...");
    m_ApiHandler.setMAction(Network::Constants::ApiAction::List);
    m_ApiHandler.pushQuery(filter);
    m_ApiHandler.Execute(ApiHandler::RequestMethod::GET, SLOT(onFetchHolidays(QNetworkReply*)));
}

void HolidayListingWidget::applyFilter(const string &currentText)
{
    string filterString = Network::Constants::Query::All;
    if(currentText == "This year") {
        filterString = Network::Constants::Query::Current;
    } else if(currentText == "Last year") {
        filterString = QString::number(QDate::currentDate().year() - 1).toStdString();
    }

    this->loadHoliday(filterString);
}

void HolidayListingWidget::createForm(QWidget *form, const string &holidayId, const bool& isBatch)
{
    form = isBatch ?
               qobject_cast<QWidget*>(new HolidayBatchForm(this)) :
               qobject_cast<QWidget*>(new HolidayForm(this, holidayId));

    connect(
        form,
        SIGNAL(HolidayFormReturned(bool,string)),
        this,
        SLOT(onHolidayFormReturned(bool,string))
    );
    connect(
        form,
        SIGNAL(HolidayFormBusy(string)),
        this,
        SLOT(onHolidayFormBusy(string))
    );
    connect(
        form,
        SIGNAL(HolidayFormReady(string)),
        this,
        SLOT(onHolidayFormReady(string))
    );

    ui->swHoliday->addWidget(form);
    ui->swHoliday->setCurrentWidget(form);
}

void HolidayListingWidget::onFetchHolidays(QNetworkReply *reply)
{
    QEventLoop eventLoop;
    connect(reply, SIGNAL(finished()), &eventLoop, SLOT(quit()));
    BaseResponse response(reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt(),
                          QString(reply->readAll()).toStdString());
    reply->deleteLater();

    if(m_HolidayModel != nullptr) {
        m_HolidayModel->deleteLater();
    }
    m_HolidayModel = new Model::HolidayModel(this);
    m_HolidayModel->populateData(response.getResponseData());
    ui->tblListHolidays->setModel(m_HolidayModel);
    // hide Id column
    ui->tblListHolidays->hideColumn(0);

    connect(
        ui->tblListHolidays->selectionModel(),
        SIGNAL(selectionChanged(QItemSelection,QItemSelection)),
        this,
        SLOT(onTableViewSelectionChanged(QItemSelection,QItemSelection))
    );


    this->setBusy(false, "Ready");
}

void HolidayListingWidget::onBtnNewHolidayClicked()
{
    this->createForm(m_HolidayForm, string(), false);
}

void HolidayListingWidget::onBtnBatchNewHolidayClicked()
{
    this->createForm(m_HolidayBatchForm, string(), true);
}

void HolidayListingWidget::onBtnEditClicked()
{
    QModelIndex index = ui->tblListHolidays->selectionModel()->currentIndex();
    // passing 0 to get the id, defined in HolidayModel::data
    // id column is hidden
    QVariant value = index.sibling(index.row(), 0).data();

    this->createForm(m_HolidayForm, value.toString().toStdString(), false);
}

void HolidayListingWidget::onCbxFilterTextChanged(const QString &currentText)
{
    this->applyFilter(currentText.toStdString());
}

void HolidayListingWidget::onCbxStatusTextChanged(const QString &currentText)
{
    QModelIndex index = ui->tblListHolidays->selectionModel()->currentIndex();
    // passing 0 to get the id, defined in HolidayModel::data
    // id column is hidden
    QVariant value = index.sibling(index.row(), 0).data();

    string holidayId = value.toString().toStdString();
    if(!holidayId.empty()) {
        QMessageBox msgBox;
        msgBox.setText("The status of the selected holiday is changed.");
        msgBox.setInformativeText("Do you want to save your changes?");
        msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
        msgBox.setDefaultButton(QMessageBox::Yes);
        int ret = msgBox.exec();

        if(ret == QMessageBox::Yes) {
            this->setBusy(true, "Updating status...");
            StatusDto statusDto;
            statusDto.setActive(currentText == "Active");

            m_ApiHandler.setMAction(Network::Constants::BLANK);
            m_ApiHandler.pushQuery(holidayId);
            m_ApiHandler.setRequestBody(statusDto.ToJson(true).dump());
            m_ApiHandler.Execute(
                ApiHandler::RequestMethod::PATCH,
                SLOT(onHolidayStatusChanged(QNetworkReply*))
            );
        }
    }
}

void HolidayListingWidget::onHolidayStatusChanged(QNetworkReply *reply)
{
    QEventLoop eventLoop;
    connect(reply, SIGNAL(finished()), &eventLoop, SLOT(quit()));
    BaseResponse response(reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt(),
                          QString(reply->readAll()).toStdString());
    reply->deleteLater();

    if(response.ResponseCode() == BaseResponse::Status::HTTP_OK) {
        this->setBusy(false, "Status updated");
        this->applyFilter(ui->cbxFilter->currentText().toStdString());
    } else {
        this->setBusy(
            false,
            QString::fromStdString(response.getResponseData()["message"])
        );
    }
}

void HolidayListingWidget::onHolidayFormBusy(string message)
{
    emit busy(QString::fromStdString(message));
}

void HolidayListingWidget::onHolidayFormReady(string message)
{
    emit ready(QString::fromStdString(message));
}

void HolidayListingWidget::onTableViewSelectionChanged(const QItemSelection &selectedItem, const QItemSelection &deselectedItem)
{
    Q_UNUSED(deselectedItem);
    ui->btnEdit->setDisabled(false);
    ui->cbxStatus->setDisabled(false);

    // only a single row is selected
    QModelIndex index = selectedItem.indexes().first();
    // passing 0 to get the id, defined in HolidayModel::data
    // id column is hidden
    QVariant value = index.sibling(index.row(), 0).data();
    HolidayDto holidayDto = m_HolidayModel->getItem(value.toString());

    ui->cbxStatus->blockSignals(true);
    ui->cbxStatus->setCurrentIndex(holidayDto.isActive() ? 0 : 1);
    ui->cbxStatus->blockSignals(false);
}

void HolidayListingWidget::onHolidayFormReturned(bool withFormSubmitSuccess, string message)
{
    QObject* sender = QObject::sender();
    ui->swHoliday->removeWidget(qobject_cast<QWidget*>(sender));
    ui->swHoliday->setCurrentWidget(ui->pgHolidayListing);
    sender->deleteLater();
    if(withFormSubmitSuccess) {
        this->loadHoliday(Network::Constants::Query::All);
    } else {
        this->setBusy(false, QString::fromStdString(message));
    }
}
