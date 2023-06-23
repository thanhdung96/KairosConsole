#ifndef ROLEFORM_H
#define ROLEFORM_H

#include <QWidget>
#include <string>
#include "Network/ApiHandler.h"
#include <QNetworkReply>

using namespace Network;

namespace Ui {
class RoleForm;
}

class RoleForm : public QWidget
{
    Q_OBJECT

public:
    explicit RoleForm(QWidget *parent = nullptr, const string& roleId = "");
    ~RoleForm();

signals:
    void RoleFormReturned(bool withFormSubmitSuccess, string message);
    void RoleFormBusy(const string& message);
    void RoleFormReady(const string& message);

private slots:
    void onFetchRoleDetail(QNetworkReply* reply);
    void onBtnReturnClicked();
    void onBtnSaveClicked();
    void onRoleSaved(QNetworkReply* reply);

private:
    Ui::RoleForm *ui;
    ApiHandler m_ApiHandler;
    string m_RoleId;

private:
    void initialiseUi();
    void loadRoleDetail(const string& roleId);
    void setBusy(bool isBusy, QString message);
};

#endif // ROLEFORM_H
