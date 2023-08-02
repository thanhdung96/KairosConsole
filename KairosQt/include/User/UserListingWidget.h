#ifndef USERLISTINGWIDGET_H
#define USERLISTINGWIDGET_H

#include <QWidget>

namespace Ui {
class UserListingWidget;
}

class UserListingWidget : public QWidget
{
    Q_OBJECT

public:
    explicit UserListingWidget(QWidget *parent = nullptr);
    ~UserListingWidget();

private:
    Ui::UserListingWidget *ui;
};

#endif // USERLISTINGWIDGET_H
