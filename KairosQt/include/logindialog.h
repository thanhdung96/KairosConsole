#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>
#include <QPushButton>
#include <QLineEdit>
#include <QString>
#include "Network/ApiHandler.h"
#include "Network/Constants/ApiConstants.h"
#include "Response/BaseResponse.h"
#include "Dto/Security/LoginDto.h"
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

public slots:
    void btnCancelClicked();
    void btnLoginClicked();

private:
    Ui::LoginDialog *ui;
    bool m_LoginSuccess;
    ApiHandler m_ApiHandler;
};

#endif  //LOGINDIALOG_H
