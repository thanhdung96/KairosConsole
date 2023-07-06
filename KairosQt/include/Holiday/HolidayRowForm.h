#ifndef HOLIDAYROWFORM_H
#define HOLIDAYROWFORM_H

#include <QWidget>
#include "Dto/Management/HolidayDto.h"
#include "Network/Helper/json.hpp"

using DTO::Management::HolidayDto;
using json = nlohmann::json;

namespace Ui {
class HolidayRowForm;
}

class HolidayRowForm : public QWidget
{
    Q_OBJECT

public:
    explicit HolidayRowForm(QWidget *parent = nullptr, const HolidayDto* holidayDto = nullptr);
    ~HolidayRowForm();

    json getData();
    size_t getId() const;
    void setId(size_t newId);
    void setSelected(bool newSelected);

public slots:
    void onBtnDeleteClicked();
    void onCbxSelectedStateChanged(int state);

signals:
    void deleted(size_t id);
    void selected(size_t id);

private:
    void initialiseUi();

private:
    Ui::HolidayRowForm *ui;
    size_t m_Id;
    bool m_Selected;
};

#endif // HOLIDAYROWFORM_H
