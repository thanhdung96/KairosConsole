#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>
#include <QCloseEvent>
#include <QObject>
#include <QNetworkReply>
#include "Network/ApiHandler.h"
using namespace Network;

namespace Ui {
class LoginDialog;
}

class LoginDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LoginDialog(QWidget *parent = nullptr);
    ~LoginDialog();

signals:
    void authenticationSuccess();
    void authenticationFailed();

public slots:
    void onFinished(QNetworkReply*);

private slots:
    void btnCancelClicked();
    void btnLoginClicked();
    void btnShowPasswordPressed();
    void btnShowPasswordReleased();

private:
    Ui::LoginDialog *ui;
    bool m_LoginSuccess;
    ApiHandler m_ApiHandler;

private:
    void closeEvent(QCloseEvent *event) override;
};

#endif  //LOGINDIALOG_H
