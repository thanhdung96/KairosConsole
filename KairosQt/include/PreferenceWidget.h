#ifndef PREFERENCEWIDGET_H
#define PREFERENCEWIDGET_H

#include <QWidget>
#include "Network/ApiHandler.h"
#include "App/Displaylanguage.h"
using namespace Network;
using namespace App;

namespace Ui {
class PreferenceWidget;
}

class PreferenceWidget : public QWidget
{
    Q_OBJECT

public:
    explicit PreferenceWidget(QWidget *parent = nullptr);
    ~PreferenceWidget();

signals:
    void busy(QString message);
    void ready(QString message);

private slots:
    void onFetchPreference(QNetworkReply* reply);
    void onBtnSavePasswordClicked();
    void onBtnSaveSettingClicked();
    void onSettingSaved(QNetworkReply* reply);
    void onPasswordChanged(QNetworkReply* reply);

private:
    Ui::PreferenceWidget *ui;
    ApiHandler m_ApiHandler;
    LstLanguage m_LstSupportedLanguages;


private:
    void setBusy(bool isBusy, QString message);
    void initialiseUi();
    void loadPreference();
};

#endif // PREFERENCEWIDGET_H
