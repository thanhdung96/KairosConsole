#include "AvailableType/AvailableTypeListingWidget.h"
#include "ui_AvailableTypeListingWidget.h"
#include <QEventLoop>
#include <QVariant>
#include <QModelIndex>
#include <Network/Helper/BaseResponse.h>
#include "Dto/App/StatusDto.h"
#include "Dto/Management/AvailableTypeDto.h"

using Network::Helper::BaseResponse;
using DTO::Management::AvailableTypeDto;
using DTO::App::StatusDto;

AvailableTypeListingWidget::AvailableTypeListingWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AvailableTypeListingWidget)
{
    ui->setupUi(this);
    m_ApiHandler.setParent(this);
    m_ApiHandler.setMDomain(Network::Constants::DEFAULT_DOMAIN);
    this->initialiseUi();
    this->loadAvailableTypes();
}

AvailableTypeListingWidget::~AvailableTypeListingWidget()
{
    m_AvailableTypeModel->deleteLater();
    if(m_AvailableTypeForm != nullptr) {
        m_AvailableTypeForm->deleteLater();
    }
    delete ui;
}

void AvailableTypeListingWidget::setBusy(bool isBusy, QString message)
{
    ui->cbxFilter->setDisabled(isBusy);
    ui->btnEdit->setDisabled(isBusy);
    ui->cbxStatus->setDisabled(isBusy);
    ui->btnNewType->setDisabled(isBusy);

    if (isBusy) {
        emit busy(message);
    } else {
        emit ready(message);
    }
}

void AvailableTypeListingWidget::initialiseUi()
{
    connect(ui->btnNewType, SIGNAL(clicked()), this, SLOT(onBtnNewTypeClicked()));
    connect(ui->btnEdit, SIGNAL(clicked()), this, SLOT(onBtnEditTypeClicked()));
    connect(
        ui->cbxFilter,
        SIGNAL(currentTextChanged(const QString&)),
        this,
        SLOT(onCbxFilterTextChanged(const QString&))
    );
    connect(
        ui->cbxStatus,
        SIGNAL(currentTextChanged(const QString&)),
        this,
        SLOT(onCbxStatusTextChanged(const QString&))
    );

    QHeaderView* tblHeader = ui->tblListTypes->horizontalHeader();
    tblHeader->setSectionResizeMode(QHeaderView::ResizeMode::Stretch);
    tblHeader->setStyleSheet("QHeaderView::section { background-color: #CDF0FF }");
    tblHeader = nullptr;

}

void AvailableTypeListingWidget::loadAvailableTypes(const string &filter)
{
    this->setBusy(true, "Loading available types...");
    m_ApiHandler.setMModel(Network::Constants::ApiModel::LeaveType);
    m_ApiHandler.setMAction(Network::Constants::ApiAction::List);
    m_ApiHandler.pushQuery(filter);
    m_ApiHandler.Execute(ApiHandler::RequestMethod::GET, SLOT(onFetchTypes(QNetworkReply*)));
}

void AvailableTypeListingWidget::applyFilter(const string &currentText)
{
    string filterString = Network::Constants::Query::All;
    if (currentText == "Active") {
        filterString = Network::Constants::Query::Active;
    } else if(currentText == "Inactive") {
        filterString = Network::Constants::Query::Inactive;
    }

    this->loadAvailableTypes(filterString);
}

void AvailableTypeListingWidget::createForm(const string &availableTypeId)
{
    m_AvailableTypeForm = new AvailableTypeForm(this, availableTypeId);
    connect(
        m_AvailableTypeForm,
        SIGNAL(TypeFormReturned(bool, string)),
        this,
        SLOT(onTypeFormReturned(bool, string))
    );
    connect(
        m_AvailableTypeForm,
        SIGNAL(TypeFormBusy(const string&)),
        this,
        SLOT(onTypeFormBusy(const string&))
    );
    connect(
        m_AvailableTypeForm,
        SIGNAL(TypeFormReady(const string&)),
        this,
        SLOT(onTypeFormReady(const string&))
    );
    ui->swType->addWidget(m_AvailableTypeForm);
    ui->swType->setCurrentWidget(m_AvailableTypeForm);

}

void AvailableTypeListingWidget::onFetchTypes(QNetworkReply *reply)
{
    QEventLoop eventLoop;
    connect(reply, SIGNAL(finished()), &eventLoop, SLOT(quit()));
    BaseResponse response(reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt(),
                          QString(reply->readAll()).toStdString());
    reply->deleteLater();

    if(m_AvailableTypeModel != nullptr) {
        m_AvailableTypeModel->deleteLater();
    }
    m_AvailableTypeModel = new Model::AvailableTypeModel(this);
    m_AvailableTypeModel->populateData(response.getResponseData());
    ui->tblListTypes->setModel(m_AvailableTypeModel);
    // hide Id column
    ui->tblListTypes->hideColumn(0);
    connect(
        ui->tblListTypes->selectionModel(),
        SIGNAL(selectionChanged(QItemSelection,QItemSelection)),
        this,
        SLOT(onTableViewSelectionChanged(QItemSelection,QItemSelection))
    );

    this->setBusy(false, "Ready");
}

void AvailableTypeListingWidget::onTypeStatusChanged(QNetworkReply *reply)
{
    QEventLoop eventLoop;
    connect(reply, SIGNAL(finished()), &eventLoop, SLOT(quit()));
    BaseResponse response(reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt(),
                          QString(reply->readAll()).toStdString());
    reply->deleteLater();

    this->applyFilter(ui->cbxFilter->currentText().toStdString());
}

void AvailableTypeListingWidget::onBtnNewTypeClicked()
{
    this->createForm(Network::Constants::BLANK);
}

void AvailableTypeListingWidget::onBtnEditTypeClicked()
{
    QModelIndex index = ui->tblListTypes->selectionModel()->currentIndex();
    // passing 0 to get the id, defined in RoleModel::data
    // id column is hidden
    QVariant value = index.sibling(index.row(), 0).data();

    this->createForm(value.toString().toStdString());
}

void AvailableTypeListingWidget::onCbxFilterTextChanged(const QString &currentText)
{
    this->applyFilter(currentText.toStdString());
}

void AvailableTypeListingWidget::onCbxStatusTextChanged(const QString &currentText)
{
    QModelIndex index = ui->tblListTypes->selectionModel()->currentIndex();
    // passing 0 to get the id, defined in RoleModel::data
    // id column is hidden
    QVariant value = index.sibling(index.row(), 0).data();

    if(value.isValid()) {
        this->setBusy(true, "Updating...");

        StatusDto statusDto;
        statusDto.setActive(currentText == "Active");

        m_ApiHandler.setMModel(Network::Constants::ApiModel::LeaveType);
        m_ApiHandler.setMAction(Network::Constants::BLANK);
        m_ApiHandler.pushQuery(value.toString().toStdString());
        m_ApiHandler.setRequestBody(statusDto.ToJson(true).dump());
        m_ApiHandler.Execute(ApiHandler::RequestMethod::PATCH, SLOT(onTypeStatusChanged(QNetworkReply*)));
    }
}

void AvailableTypeListingWidget::onTypeFormReturned(bool submitSuccess, string message)
{
    ui->swType->removeWidget(m_AvailableTypeForm);
    ui->swType->setCurrentWidget(ui->pgTypeListing);
    m_AvailableTypeForm->deleteLater();

    if(submitSuccess) {
        this->applyFilter(ui->cbxFilter->currentText().toStdString());
    } else {
        this->setBusy(false, QString::fromStdString(message));
    }
}

void AvailableTypeListingWidget::onTypeFormBusy(const string &message)
{
    this->setBusy(true, QString::fromStdString(message));
}

void AvailableTypeListingWidget::onTypeFormReady(const string &message)
{
    this->setBusy(false, QString::fromStdString(message));
}

void AvailableTypeListingWidget::onTableViewSelectionChanged(
    const QItemSelection &selectedItem,
    const QItemSelection &deselectedItem
) {
    Q_UNUSED(deselectedItem);
    ui->btnEdit->setDisabled(false);
    ui->cbxStatus->setDisabled(false);

    // only a single row is selected
    QModelIndex index = selectedItem.indexes().first();
    // passing 0 to get the id, defined in RoleModel::data
    // id column is hidden
    QVariant value = index.sibling(index.row(), 0).data();
    AvailableTypeDto typeDto = m_AvailableTypeModel->getItem(value.toString());

    ui->cbxStatus->blockSignals(true);
    ui->cbxStatus->setCurrentIndex(typeDto.isActive() ? 0 : 1);
    ui->cbxStatus->blockSignals(false);
}
