#ifndef AVAILABLETYPEFORM_H
#define AVAILABLETYPEFORM_H

#include <QWidget>
#include <QNetworkReply>
#include <string>
#include "Network/ApiHandler.h"

using std::string;
using Network::ApiHandler;

namespace Ui {
class AvailableTypeForm;
}

class AvailableTypeForm : public QWidget
{
    Q_OBJECT

public:
    explicit AvailableTypeForm(QWidget *parent = nullptr, const string& typeId = "");
    ~AvailableTypeForm();

signals:
    void TypeFormReturned(bool withFormSubmitSuccess, string message);
    void TypeFormBusy(const string& message);
    void TypeFormReady(const string& message);

private slots:
    void onFetchTypeDetail(QNetworkReply* reply);
    void onBtnSaveClicked();
    void onBtnReturnClicked();

    void onAvailableTypeSaved(QNetworkReply* reply);

private:
    void loadTypeDetail();
    void initialiseUi();
    void setBusy(bool isBusy, QString message);

private:
    Ui::AvailableTypeForm *ui;
    ApiHandler m_ApiHandler;
    string m_TypeId;
};

#endif // AVAILABLETYPEFORM_H
