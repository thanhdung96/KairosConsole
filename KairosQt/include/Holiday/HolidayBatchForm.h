#ifndef HOLIDAYBATCHFORM_H
#define HOLIDAYBATCHFORM_H

#include <QWidget>
#include <QNetworkReply>
#include <string>
#include <vector>
#include "Network/ApiHandler.h"
#include "Holiday/HolidayRowForm.h"

using Network::ApiHandler;
using std::string;
using std::vector;

typedef vector<HolidayRowForm*> LstHolidayRows;

namespace Ui {
class HolidayBatchForm;
}

class HolidayBatchForm : public QWidget
{
    Q_OBJECT

public:
    explicit HolidayBatchForm(QWidget *parent = nullptr);
    ~HolidayBatchForm();

signals:
    void HolidayFormReturned(bool withFormSubmitSuccess, string message);
    void HolidayFormBusy(const string& message);
    void HolidayFormReady(const string& message);
    void busy(QString message);
    void ready(QString message);

private slots:
    void onBtnSaveClicked();
    void onBtnReturnClicked();
    void onFetchSamples(QNetworkReply* reply);
    void onHolidaysSaved(QNetworkReply* reply);
    void onRowFormDeleted(size_t id);
    void onRowFormSelected(size_t id);
    void onBtnNewClicked();
    void onBtnUpClicked();
    void onBtnDownClicked();

private:
    void setBusy(bool isBusy, QString message);
    void initialiseUi();
    void generateSamples();
    void reassignIdToRowForms();
    void connectRowForm(HolidayRowForm* rowForm);

private:
    Ui::HolidayBatchForm *ui;
    ApiHandler m_ApiHandler;
    LstHolidayRows m_LstHolidayRows;
    HolidayRowForm* m_SelectedRow = nullptr;
};

#endif // HOLIDAYBATCHFORM_H
