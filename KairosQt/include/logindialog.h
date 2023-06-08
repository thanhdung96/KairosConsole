#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>
#include <QPushButton>
#include <QLineEdit>
#include <QString>
#include "Network/ApiHandler.h"
#include "Network/Constants/ApiConstants.h"
#include "Network/Helper/BaseResponse.h"
#include "Dto/Security/LoginDto.h"
#include "App/Session.h"

using namespace App;
using namespace Network;
using namespace DTO::Security;

namespace Ui {
class LoginDialog;
}

class LoginDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LoginDialog(QWidget *parent = nullptr);
    ~LoginDialog();

    bool getLoginSuccess() const;
    void setLoginSuccess(bool newLoginSuccess);

private slots:
    void btnCancelClicked();
    void btnLoginClicked();
    void btnShowPasswordPressed();
    void btnShowPasswordReleased();
    void getResponse(BaseResponse response);

private:
    Ui::LoginDialog *ui;
    bool m_LoginSuccess;
    ApiHandler m_ApiHandler;
};

#endif  //LOGINDIALOG_H
