#include "Model/UserModel.h"

namespace Model {
    UserModel::UserModel(QObject *parent)
        : QAbstractItemModel(parent)
    {
    }

    QVariant UserModel::headerData(int section, Qt::Orientation orientation, int role) const
    {
        // FIXME: Implement me!
    }

    QModelIndex UserModel::index(int row, int column, const QModelIndex &parent) const
    {
        // FIXME: Implement me!
    }

    QModelIndex UserModel::parent(const QModelIndex &index) const
    {
        // FIXME: Implement me!
    }

    int UserModel::rowCount(const QModelIndex &parent) const
    {
        if (!parent.isValid())
            return 0;

        // FIXME: Implement me!
    }

    int UserModel::columnCount(const QModelIndex &parent) const
    {
        if (!parent.isValid())
            return 0;

        // FIXME: Implement me!
    }

    QVariant UserModel::data(const QModelIndex &index, int role) const
    {
        if (!index.isValid())
            return QVariant();

        // FIXME: Implement me!
        return QVariant();
    }

    bool UserModel::insertRows(int row, int count, const QModelIndex &parent)
    {
        beginInsertRows(parent, row, row + count - 1);
        // FIXME: Implement me!
        endInsertRows();
        return true;
    }

    bool UserModel::insertColumns(int column, int count, const QModelIndex &parent)
    {
        beginInsertColumns(parent, column, column + count - 1);
        // FIXME: Implement me!
        endInsertColumns();
        return true;
    }

    bool UserModel::removeRows(int row, int count, const QModelIndex &parent)
    {
        beginRemoveRows(parent, row, row + count - 1);
        // FIXME: Implement me!
        endRemoveRows();
        return true;
    }

    bool UserModel::removeColumns(int column, int count, const QModelIndex &parent)
    {
        beginRemoveColumns(parent, column, column + count - 1);
        // FIXME: Implement me!
        endRemoveColumns();
        return true;
    }

    void UserModel::populateData(const json &lstUserDto)
    {
        m_LstUsers.clear();
        for(size_t i = 0; i < lstUserDto.size(); i += 1) {
            UserDto userDto;
            userDto.FromJson(lstUserDto[i]);
            m_LstUsers.push_back(userDto);
        }
    }

    const UserDto &UserModel::getItem(const QString &userId)
    {
        for(size_t i = 0; i < m_LstUsers.size(); i += 1) {
            if(m_LstUsers.at(i).getId() == userId.toStdString()) {
                return m_LstUsers.at(i);
            }
        }

        return UserDto();
    }
}
