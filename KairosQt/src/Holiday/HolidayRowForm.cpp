#include "Holiday/HolidayRowForm.h"
#include "ui_HolidayRowForm.h"
#include <QDate>

HolidayRowForm::HolidayRowForm(QWidget *parent, const HolidayDto* holidayDto) :
    QWidget(parent),
    ui(new Ui::HolidayRowForm)
{
    ui->setupUi(this);
    this->initialiseUi();

    ui->txtName->setText(QString::fromStdString(holidayDto->getName()));
    ui->deStartDate->setDate(
        QDate::fromString(QString::fromStdString(holidayDto->getStartDate()), "yyyy-MM-dd")
    );
    ui->deEndDate->setDate(
        QDate::fromString(QString::fromStdString(holidayDto->getEndDate()), "yyyy-MM-dd")
    );
    ui->cbxRecurrent->setChecked(holidayDto->isRecurrence());
}

HolidayRowForm::~HolidayRowForm()
{
    delete ui;
}

json HolidayRowForm::getData()
{
    QDate startDate = ui->deStartDate->date();
    HolidayDto holidayDto;
    holidayDto.setName(ui->txtName->text().toStdString());
    holidayDto.setStartDate(ui->deStartDate->date().toString("yyyy-MM-dd").toStdString());
    holidayDto.setEndDate(ui->deEndDate->date().toString("yyyy-MM-dd").toStdString());
    holidayDto.setYear(startDate.year());
    holidayDto.setActive(true);
    holidayDto.setRecurrence(ui->cbxRecurrent->isChecked());

    return holidayDto.ToJson(false);
}

void HolidayRowForm::onBtnDeleteClicked()
{
    emit deleted(m_Id);
}

void HolidayRowForm::onCbxSelectedStateChanged(int state)
{
    emit selected(m_Id);
}

void HolidayRowForm::initialiseUi()
{
    connect(ui->btnDelete, SIGNAL(clicked()), this, SLOT(onBtnDeleteClicked()));
    connect(ui->cbxSelected, SIGNAL(stateChanged(int)), this, SLOT(onCbxSelectedStateChanged(int)));
}

void HolidayRowForm::setSelected(bool newSelected)
{
    m_Selected = newSelected;

    // temporarily block signal to prevent emitting stateChanged signal to HolidayBatchForm
    // for this checked status is set manually
    ui->cbxSelected->blockSignals(true);
    ui->cbxSelected->setChecked(newSelected);
    ui->cbxSelected->blockSignals(false);
}

size_t HolidayRowForm::getId() const
{
    return m_Id;
}

void HolidayRowForm::setId(size_t newId)
{
    m_Id = newId;
}
