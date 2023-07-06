#include "Model/HolidayModel.h"

namespace Model {
    HolidayModel::HolidayModel(QObject *parent)
        : QAbstractItemModel(parent)
    {
        m_HeaderMapper[0] = QString("Id");
        m_HeaderMapper[1] = QString("Name");
        m_HeaderMapper[2] = QString("Year");
        m_HeaderMapper[3] = QString("Start Date");
        m_HeaderMapper[4] = QString("End Date");
        m_HeaderMapper[5] = QString("Active");
    }

    QVariant HolidayModel::headerData(int section, Qt::Orientation orientation, int role) const
    {
        if (role == Qt::DisplayRole && orientation == Qt::Horizontal) {
            return m_HeaderMapper.at(section);
        }

        return QVariant();

    }

    QModelIndex HolidayModel::index(int row, int column, const QModelIndex &parent) const
    {
        return hasIndex(row, column, parent) ? createIndex(row, column) : QModelIndex();
    }

    QModelIndex HolidayModel::parent(const QModelIndex &index) const
    {
        return QModelIndex();
    }

    int HolidayModel::rowCount(const QModelIndex &parent) const
    {
        Q_UNUSED(parent);

        return m_LstHolidays.size();
    }

    int HolidayModel::columnCount(const QModelIndex &parent) const
    {
        Q_UNUSED(parent);

        return m_HeaderMapper.size();
    }

    QVariant HolidayModel::data(const QModelIndex &index, int role) const
    {
        if (!index.isValid() || role != Qt::DisplayRole) {
            return QVariant();
        }

        switch (index.column()) {
            case 0:
                return QString::fromStdString(m_LstHolidays.at(index.row()).getId());
                break;
            case 1:
                return QString::fromStdString(m_LstHolidays.at(index.row()).getName());
                break;
            case 2:
                return QString::number(m_LstHolidays.at(index.row()).getYear());
                break;
            case 3:
                return QString::fromStdString(m_LstHolidays.at(index.row()).getStartDate());
                break;
            case 4:
                return QString::fromStdString(m_LstHolidays.at(index.row()).getEndDate());
                break;
            case 5:
                return m_LstHolidays.at(index.row()).isActive() ? "Active" : "Inactive";
                break;
            default:
                return QVariant();
                break;
        }
    }

    void HolidayModel::populateData(const json &lstHolidayDto)
    {
        m_LstHolidays.clear();
        for(size_t i = 0; i < lstHolidayDto.size(); i += 1) {
            HolidayDto holidayDto;
            holidayDto.FromJson(lstHolidayDto[i]);
            m_LstHolidays.push_back(holidayDto);
        }
    }
}
