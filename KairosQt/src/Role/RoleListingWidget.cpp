#include "Role/RoleListingWidget.h"
#include "ui_RoleListingWidget.h"
#include "Dto/App/StatusDto.h"
#include "Dto/Management/RoleDto.h"
#include "Network/Helper/BaseResponse.h"
#include <QEventLoop>

using Network::Helper::BaseResponse;
using DTO::Management::RoleDto;
using DTO::App::StatusDto;

RoleListingWidget::RoleListingWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RoleListing)
{
    ui->setupUi(this);
    m_ApiHandler.setParent(this);
    m_ApiHandler.setMModel(Constants::ApiModel::Role);
    m_ApiHandler.setMDomain(Constants::DEFAULT_DOMAIN);

    this->initialiseUi();
    this->loadRoles();
}

RoleListingWidget::~RoleListingWidget()
{
    m_RoleModel->deleteLater();
    if(m_RoleForm != nullptr) {
        m_RoleForm->deleteLater();
    }
    delete ui;
}

void RoleListingWidget::initialiseUi()
{
    connect(ui->btnNewRole, SIGNAL(clicked()), this, SLOT(onBtnNewRoleClicked()));
    connect(ui->btnEdit, SIGNAL(clicked()), this, SLOT(onBtnEditRoleClicked()));
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

    QHeaderView* tblHeader = ui->tblListRoles->horizontalHeader();
    tblHeader->setSectionResizeMode(QHeaderView::ResizeMode::Stretch);
    tblHeader->setStyleSheet("QHeaderView::section { background-color: #CDF0FF }");
    tblHeader = nullptr;
}

void RoleListingWidget::loadRoles(const string& filter)
{
    this->setBusy(true, "Loading available roles...");
    m_ApiHandler.setMAction(Constants::ApiAction::List);
    m_ApiHandler.pushQuery(filter);
    m_ApiHandler.Execute(ApiHandler::RequestMethod::GET, SLOT(onFetchRoles(QNetworkReply*)));
}

void RoleListingWidget::applyFilter(const string &currentText)
{
    string filterString = Constants::Query::All;
    if (currentText == "Active") {
        filterString = Constants::Query::Active;
    } else if(currentText == "Inactive") {
        filterString = Constants::Query::Inactive;
    }

    this->loadRoles(filterString);
}

void RoleListingWidget::createForm(const string &roleId)
{
    m_RoleForm = new RoleForm(this, roleId);
    connect(m_RoleForm, SIGNAL(RoleFormReturned(bool,string)), this, SLOT(onRoleFormReturned(bool,string)));
    ui->swRole->addWidget(m_RoleForm);
    ui->swRole->setCurrentWidget(m_RoleForm);
}

void RoleListingWidget::onFetchRoles(QNetworkReply *reply)
{
    QEventLoop eventLoop;
    connect(reply, SIGNAL(finished()), &eventLoop, SLOT(quit()));
    BaseResponse response(reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt(),
                          QString(reply->readAll()).toStdString());
    reply->deleteLater();

    if(m_RoleModel != nullptr) {
        m_RoleModel->deleteLater();
    }
    m_RoleModel = new Model::RoleModel(this);
    m_RoleModel->populateData(response.getResponseData());
    ui->tblListRoles->setModel(m_RoleModel);
    // hide Id column
    ui->tblListRoles->hideColumn(0);
    connect(
        ui->tblListRoles->selectionModel(),
        SIGNAL(selectionChanged(QItemSelection,QItemSelection)),
        this,
        SLOT(onTableViewSelectionChanged(QItemSelection,QItemSelection))
    );

    this->setBusy(false, "Ready");
}

void RoleListingWidget::onBtnNewRoleClicked()
{
    this->createForm(Network::Constants::BLANK);
}

void RoleListingWidget::onBtnEditRoleClicked()
{
    QModelIndex index = ui->tblListRoles->selectionModel()->currentIndex();
    // passing 0 to get the id, defined in RoleModel::data
    // id column is hidden
    QVariant value = index.sibling(index.row(), 0).data();

    if(value.isValid()) {
        this->createForm(value.toString().toStdString());
    }
}

void RoleListingWidget::onCbxFilterTextChanged(const QString& currentText)
{
    this->applyFilter(currentText.toStdString());
}

void RoleListingWidget::onCbxStatusTextChanged(const QString &currentText)
{
    QModelIndex index = ui->tblListRoles->selectionModel()->currentIndex();
    // passing 0 to get the id, defined in RoleModel::data
    // id column is hidden
    QVariant value = index.sibling(index.row(), 0).data();

    if(value.isValid()) {
        this->setBusy(true, "Updating...");

        StatusDto statusDto;
        statusDto.setActive(currentText == "Active");

        m_ApiHandler.setMAction(Network::Constants::BLANK);
        m_ApiHandler.pushQuery(value.toString().toStdString());
        m_ApiHandler.setRequestBody(statusDto.ToJson(true).dump());
        m_ApiHandler.Execute(ApiHandler::RequestMethod::PATCH, SLOT(onRoleStatusChanged(QNetworkReply*)));
    }
}

void RoleListingWidget::onRoleStatusChanged(QNetworkReply *reply)
{
    QEventLoop eventLoop;
    connect(reply, SIGNAL(finished()), &eventLoop, SLOT(quit()));
    BaseResponse response(reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt(),
                          QString(reply->readAll()).toStdString());
    reply->deleteLater();

    this->applyFilter(ui->cbxFilter->currentText().toStdString());
}

void RoleListingWidget::onRoleFormReturned(bool withFormSubmitSuccess, string message)
{
    ui->swRole->removeWidget(m_RoleForm);
    ui->swRole->setCurrentWidget(ui->pgRoleListing);
    m_RoleForm->deleteLater();
    if(withFormSubmitSuccess) {
        this->loadRoles();
    }
}

void RoleListingWidget::onRoleFormBusy(const string &message)
{
    this->setBusy(true, QString::fromStdString(message));
}

void RoleListingWidget::onRoleFormReady(const string &message)
{
    this->setBusy(false, QString::fromStdString(message));
}

void RoleListingWidget::onTableViewSelectionChanged(
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
    RoleDto roleDto = m_RoleModel->getItem(value.toString());

    ui->cbxStatus->blockSignals(true);
    ui->cbxStatus->setCurrentIndex(roleDto.isActive() ? 0 : 1);
    ui->cbxStatus->blockSignals(false);
}

void RoleListingWidget::setBusy(bool isBusy, QString message)
{
    ui->cbxFilter->setDisabled(isBusy);
    ui->btnEdit->setDisabled(isBusy);
    ui->cbxStatus->setDisabled(isBusy);
    ui->btnNewRole->setDisabled(isBusy);

    if (isBusy) {
        emit busy(message);
    } else {
        emit ready(message);
    }
}
