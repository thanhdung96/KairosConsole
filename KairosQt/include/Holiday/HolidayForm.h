#ifndef HOLIDAYFORM_H
#define HOLIDAYFORM_H

#include <QWidget>
#include <QNetworkReply>
#include <string>
#include "Network/ApiHandler.h"

using Network::ApiHandler;
using std::string;

namespace Ui {
class HolidayForm;
}

class HolidayForm : public QWidget
{
    Q_OBJECT

public:
    explicit HolidayForm(QWidget *parent = nullptr, const string& holidayId = "");
    ~HolidayForm();

signals:
    void HolidayFormReturned(bool withFormSubmitSuccess, string message);
    void HolidayFormBusy(string message);
    void HolidayFormReady(string message);

private slots:
    void onFetchHolidayDetail(QNetworkReply* reply);
    void onBtnReturnClicked();
    void onBtnSaveClicked();
    void onHolidaySaved(QNetworkReply* reply);

private:
    Ui::HolidayForm *ui;
    ApiHandler m_ApiHandler;
    string m_HolidayId;

private:
    void initialiseUi();
    void loadHolidayDetail(const string& holidayId);
    void setBusy(bool isBusy, QString message);

};

#endif // HOLIDAYFORM_H
