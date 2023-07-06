#ifndef HOLIDAYLISTINGWIDGET_H
#define HOLIDAYLISTINGWIDGET_H

#include <QWidget>
#include <QNetworkReply>
#include <string>
#include "Network/ApiHandler.h"
#include "Model/HolidayModel.h"
#include "Network/Constants/ApiConstants.h"
#include "HolidayForm.h"
#include "HolidayBatchForm.h"

using Network::ApiHandler;
using std::string;

namespace Ui {
class HolidayListingWidget;
}

class HolidayListingWidget : public QWidget
{
    Q_OBJECT

public:
    explicit HolidayListingWidget(QWidget *parent = nullptr);
    ~HolidayListingWidget();

signals:
    void busy(QString message);
    void ready(QString message);

private:
    void setBusy(bool isBusy, QString message);
    void initialiseUi();
    void loadHoliday(const string& filter = Network::Constants::Query::All);
    void applyFilter(const string& currentText);
    void createForm(QWidget* form, const string& holidayId = string(), const bool& isBatch = false);

private slots:
    void onFetchHolidays(QNetworkReply* reply);
    void onBtnNewHolidayClicked();
    void onBtnBatchNewHolidayClicked();
    void onBtnEditClicked();
    void onCbxFilterTextChanged(const QString&);
    void onCbxStatusTextChanged(const QString&);
    void onHolidayStatusChanged(QNetworkReply* reply);

    void onHolidayFormReturned(bool withFormSubmitSuccess, string message);
    void onHolidayFormBusy(string message);
    void onHolidayFormReady(string message);

private:
    Ui::HolidayListingWidget *ui;
    ApiHandler m_ApiHandler;
    Model::HolidayModel* m_HolidayModel = nullptr;
    HolidayForm* m_HolidayForm = nullptr;
    HolidayBatchForm* m_HolidayBatchForm = nullptr;
};

#endif // HOLIDAYLISTINGWIDGET_H
