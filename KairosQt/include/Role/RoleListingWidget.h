#ifndef ROLELISTINGWIDGET_H
#define ROLELISTINGWIDGET_H

#include <string>
#include <QWidget>
#include <QNetworkReply>
#include <QItemSelectionModel>
#include "Network/ApiHandler.h"
#include "Model/RoleModel.h"
#include "Role/RoleForm.h"
#include "Network/Constants/ApiConstants.h"
using namespace Network;

namespace Ui {
class RoleListing;
}

class RoleListingWidget : public QWidget
{
    Q_OBJECT

public:
    explicit RoleListingWidget(QWidget *parent = nullptr);
    ~RoleListingWidget();

signals:
    void busy(QString message);
    void ready(QString message);

private:
    void setBusy(bool isBusy, QString message);
    void initialiseUi();
    void loadRoles(const string& filter = Constants::Query::All);
    void applyFilter(const string& currentText);
    void createForm(const string& roleId);

private slots:
    void onFetchRoles(QNetworkReply* reply);
    void onBtnNewRoleClicked();
    void onBtnEditRoleClicked();
    void onCbxFilterTextChanged(const QString&);
    void onCbxStatusTextChanged(const QString&);
    void onRoleStatusChanged(QNetworkReply* reply);

    void onRoleFormReturned(bool withFormSubmitSuccess, string message);
    void onRoleFormBusy(const string& message);
    void onRoleFormReady(const string& message);

    void onTableViewSelectionChanged(
        const QItemSelection& selectedItem,
        const QItemSelection& deselectedItem
    );

private:
    Ui::RoleListing *ui;
    ApiHandler m_ApiHandler;
    Model::RoleModel* m_RoleModel = nullptr;
    RoleForm* m_RoleForm = nullptr;
};

#endif // ROLELISTINGWIDGET_H
