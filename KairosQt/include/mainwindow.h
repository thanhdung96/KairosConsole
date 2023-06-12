#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QNetworkReply>
#include "Network/ApiHandler.h"

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

private:
    Ui::MainWindow *ui;
    ApiHandler m_ApiHandler;
};
#endif // MAINWINDOW_H
