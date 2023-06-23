#ifndef ROLEMODEL_H
#define ROLEMODEL_H

#include <QAbstractItemModel>
#include <QList>
#include "Dto/Management/RoleDto.h"
#include "Network/Helper/json.hpp"

namespace Model {
using namespace DTO::Management;
using json = nlohmann::json;
    class RoleModel : public QAbstractItemModel
    {
        Q_OBJECT

        public:
            explicit RoleModel(QObject *parent = nullptr);

            // Header:
            QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

            // Basic functionality:
            QModelIndex index(int row, int column,
                              const QModelIndex &parent = QModelIndex()) const override;
            QModelIndex parent(const QModelIndex &index) const override;

            int rowCount(const QModelIndex &parent = QModelIndex()) const override;
            int columnCount(const QModelIndex &parent = QModelIndex()) const override;
            QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

            // Add data:
            bool insertRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;
            bool insertColumns(int column, int count, const QModelIndex &parent = QModelIndex()) override;

            // Remove data:
            bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;
            bool removeColumns(int column, int count, const QModelIndex &parent = QModelIndex()) override;

            void populateData(json lstRoleDto);

        private:
            QList<RoleDto> m_LstRoles;
    };
};


#endif // ROLEMODEL_H
