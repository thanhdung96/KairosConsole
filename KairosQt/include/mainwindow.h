#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <vector>
#include <QNetworkReply>
#include <QPushButton>
#include "Network/ApiHandler.h"
#include "App/myprofilewidget.h"
#include "App/PreferenceWidget.h"
#include "Role/RoleListingWidget.h"
#include "AvailableType/AvailableTypeListingWidget.h"

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
    void onBtnSideTitleClicked();
    void onBtnSideHolidaysClicked();
    void onBtnSideLeaveTypesClicked();
    void onBtnSideEmployeesClicked();
    void onBtnSideImportClicked();

    void onWidgetBusy(QString message);
    void onWidgetReady(QString message);

private:
    typedef vector<QPushButton*> LstButtons;

    Ui::MainWindow *ui;
    ApiHandler m_ApiHandler;
    MyProfileWidget* m_MyProfileWg = nullptr;
    PreferenceWidget* m_PreferenceWg = nullptr;
    RoleListingWidget* m_RoleListingWg = nullptr;
    AvailableTypeListingWidget* m_TypeListingWidget = nullptr;
    LstButtons m_LstSideBtns;

private:
    void initialiseUI();
    void loadProfile();
    void deleteCurrentWidget();
    void checkListSideButtons(QPushButton* selectedSideBtn);
};
#endif // MAINWINDOW_H
