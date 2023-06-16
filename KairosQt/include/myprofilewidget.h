#ifndef MYPROFILEWIDGET_H
#define MYPROFILEWIDGET_H

#include <QWidget>
#include "Network/ApiHandler.h"
#include "Dto/App/ProfileDto.h"

using namespace Network;
using namespace DTO::App;

namespace Ui {
class MyProfileWidget;
}

class MyProfileWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MyProfileWidget(QWidget *parent = nullptr);
    ~MyProfileWidget();

signals:
    void busy(QString message);
    void ready(QString message);

private slots:
    void onFetchProfile(QNetworkReply* reply);
    void onPatchedProfile(QNetworkReply* reply);
    void onBtnSaveClicked();

private:
    Ui::MyProfileWidget *ui;
    ApiHandler m_ApiHandler;
    ProfileDto m_ProfileDto;

private:
    void loadProfile();
    void initialiseUi();
    void setBusy(bool isBusy, QString message);
};

#endif // MYPROFILEWIDGET_H
