#ifndef HOLIDAYMODEL_H
#define HOLIDAYMODEL_H

#include <QAbstractItemModel>
#include <QList>
#include <map>
#include "Dto/Management/HolidayDto.h"
#include "Network/Helper/json.hpp"

namespace Model {
using json = nlohmann::json;
using std::map;
using DTO::Management::HolidayDto;
typedef map<size_t, QString> HeaderMapper;

    class HolidayModel : public QAbstractItemModel
    {
        Q_OBJECT

        public:
            explicit HolidayModel(QObject *parent = nullptr);

            // Header:
            QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

            // Basic functionality:
            QModelIndex index(int row, int column,
                              const QModelIndex &parent = QModelIndex()) const override;
            QModelIndex parent(const QModelIndex &index) const override;

            int rowCount(const QModelIndex &parent = QModelIndex()) const override;
            int columnCount(const QModelIndex &parent = QModelIndex()) const override;

            QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

            void populateData(const json& lstHolidayDto);
            const HolidayDto& getItem(const QString& holidayId);

        private:
            QList<HolidayDto> m_LstHolidays;
            HeaderMapper m_HeaderMapper;
    };
}

#endif // HOLIDAYMODEL_H
