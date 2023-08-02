#ifndef USERMODEL_H
#define USERMODEL_H

#include <QList>
#include <QAbstractItemModel>
#include "Dto/Management/UserDto.h"
#include "Network/Helper/json.hpp"

namespace Model {
using json = nlohmann::json;
using DTO::Management::UserDto;

    class UserModel : public QAbstractItemModel
    {
        Q_OBJECT

        public:
            explicit UserModel(QObject *parent = nullptr);

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

            void populateData(const json& lstUserDto);
            const UserDto& getItem(const QString& userId);

        private:
            QList<UserDto> m_LstUsers;
    };
}


#endif // USERMODEL_H
