#include "Role/RoleListingWidget.h"
#include "ui_RoleListingWidget.h"
#include "Network/Helper/BaseResponse.h"
#include <QEventLoop>

using Network::Helper::BaseResponse;

RoleListingWidget::RoleListingWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RoleListing)
{
    ui->setupUi(this);
    m_ApiHandler.setParent(this);
    m_ApiHandler.setMDomain(Constants::DEFAULT_DOMAIN);

    m_ApiHandler.setParent(this);
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

    QHeaderView* tblHeader = ui->tblListRoles->horizontalHeader();
    tblHeader->setSectionResizeMode(QHeaderView::ResizeMode::Stretch);
    tblHeader->setStyleSheet("QHeaderView::section { background-color: #CDF0FF }");
}

void RoleListingWidget::loadRoles(const string& filter)
{
    this->setBusy(true, "Loading available roles...");
    m_ApiHandler.setMModel(Constants::ApiModel::Role);
    m_ApiHandler.setMAction(Constants::ApiAction::List);
    m_ApiHandler.pushQuery(filter);
    m_ApiHandler.Execute(ApiHandler::RequestMethod::GET, SLOT(onFetchRoles(QNetworkReply*)));
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

    this->setBusy(false, "Ready");
}

void RoleListingWidget::onBtnNewRoleClicked()
{
    m_RoleForm = new RoleForm(this, "");
    connect(m_RoleForm, SIGNAL(RoleFormReturned(bool,string)), this, SLOT(onRoleFormReturned(bool,string)));
    ui->swRole->addWidget(m_RoleForm);
    ui->swRole->setCurrentWidget(m_RoleForm);
}

void RoleListingWidget::onBtnEditRoleClicked()
{
    QModelIndex index = ui->tblListRoles->selectionModel()->currentIndex();
    // passing 0 to get the id, defined in RoleModel::data
    // id column is hidden
    QVariant value = index.sibling(index.row(), 0).data();

    m_RoleForm = new RoleForm(this, value.toString().toStdString());
    connect(m_RoleForm, SIGNAL(RoleFormReturned(bool,string)), this, SLOT(onRoleFormReturned(bool,string)));
    ui->swRole->addWidget(m_RoleForm);
    ui->swRole->setCurrentWidget(m_RoleForm);
}

void RoleListingWidget::onCbxFilterTextChanged(const QString& currentText)
{
    string filterString = Constants::Query::All;
    if (currentText == "Active") {
        filterString = Constants::Query::Active;
    } else if(currentText == "Inactive") {
        filterString = Constants::Query::Inactive;
    }

    this->loadRoles(filterString);
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
