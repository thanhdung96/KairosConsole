#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <QNetworkReply>
#include "Network/ApiHandler.h"
#include "myprofilewidget.h"
#include "PreferenceWidget.h"

using namespace Network;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onFetchProfile(QNetworkReply* reply);

    void onActionQuitTriggered(bool checked);
    void onActionMyProfileTriggered(bool checked);
    void onActionPreferenceTriggered(bool checked);

    void onWidgetBusy(QString message);
    void onWidgetReady(QString message);

private:
    Ui::MainWindow *ui;
    ApiHandler m_ApiHandler;
    MyProfileWidget* m_MyProfileWg = nullptr;
    PreferenceWidget* m_PreferenceWg = nullptr;

private:
    void initialiseUI();
    void loadProfile();
    void deleteCurrentWidget();
};
#endif // MAINWINDOW_H
