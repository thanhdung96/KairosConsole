#ifndef AVAILABLETYPELISTINGWIDGET_H
#define AVAILABLETYPELISTINGWIDGET_H

#include <QWidget>
#include <string>
#include <QNetworkReply>
#include <QItemSelection>
#include "Network/ApiHandler.h"
#include "Network/Constants/ApiConstants.h"
#include "Model/AvailableTypeModel.h"
#include "AvailableTypeForm.h"

using std::string;
using Network::ApiHandler;
using Model::AvailableTypeModel;

namespace Ui {
class AvailableTypeListingWidget;
}

class AvailableTypeListingWidget : public QWidget
{
    Q_OBJECT

public:
    explicit AvailableTypeListingWidget(QWidget *parent = nullptr);
    ~AvailableTypeListingWidget();

signals:
    void busy(QString message);
    void ready(QString message);

private:
    void setBusy(bool isBusy, QString message);
    void initialiseUi();
    void loadAvailableTypes(const string& filter = Network::Constants::Query::All);
    void applyFilter(const string& filterString);

private slots:
    void onFetchTypes(QNetworkReply* reply);
    void onTypeStatusChanged(QNetworkReply* reply);
    void onBtnNewTypeClicked();
    void onBtnEditTypeClicked();
    void onCbxFilterTextChanged(const QString&);
    void onCbxStatusTextChanged(const QString&);

    void onTypeFormReturned(bool submitSuccess, string message);

    void onTableViewSelectionChanged(
        const QItemSelection& selectedItem,
        const QItemSelection& deselectedItem
    );

private:
    Ui::AvailableTypeListingWidget *ui;
    ApiHandler m_ApiHandler;
    AvailableTypeModel* m_AvailableTypeModel = nullptr;
    AvailableTypeForm* m_AvailableTypeForm = nullptr;
};

#endif // AVAILABLETYPELISTINGWIDGET_H
