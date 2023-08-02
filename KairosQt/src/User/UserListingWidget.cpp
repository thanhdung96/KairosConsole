#include "User/UserListingWidget.h"
#include "ui_userlistingwidget.h"

UserListingWidget::UserListingWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::UserListingWidget)
{
    ui->setupUi(this);
}

UserListingWidget::~UserListingWidget()
{
    delete ui;
}
