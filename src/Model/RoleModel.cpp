#include "Model/RoleModel.h"

namespace Model {
    RoleModel::RoleModel(QObject *parent) : QAbstractItemModel(parent)
    {

    }

    QVariant RoleModel::headerData(int section, Qt::Orientation orientation, int role) const
    {
        // FIXME: Implement me!
        if (role == Qt::DisplayRole && orientation == Qt::Horizontal) {
            if(section == 0) {
                return QString("Id");
            } else if (section == 1) {
                return QString("Name");
            } else if (section == 2) {
                return QString("Description");
            } else if (section == 3) {
                return QString("Active");
            }
        }

        return QVariant();
    }

    QModelIndex RoleModel::index(int row, int column, const QModelIndex &parent) const
    {
        return hasIndex(row, column, parent) ? createIndex(row, column) : QModelIndex();
    }

    QModelIndex RoleModel::parent(const QModelIndex &index) const
    {
        return QModelIndex();
    }

    int RoleModel::rowCount(const QModelIndex &parent) const
    {
        Q_UNUSED(parent);

        return m_LstRoles.size();
    }

    int RoleModel::columnCount(const QModelIndex &parent) const
    {
        Q_UNUSED(parent);

        return 4;
    }

    QVariant RoleModel::data(const QModelIndex &index, int role) const
    {
        if (!index.isValid() || role != Qt::DisplayRole) {
            return QVariant();
        }

        if(index.column() == 0) {
            return QString::fromStdString(m_LstRoles.at(index.row()).getId());
        } else if(index.column() == 1) {
            return QString::fromStdString(m_LstRoles.at(index.row()).getName());
        } else if(index.column() == 2) {
            return QString::fromStdString(m_LstRoles.at(index.row()).getDescription());
        } else if(index.column() == 3) {
            return m_LstRoles.at(index.row()).isActive() ? "Active" : "Inactive";
        }
    }

    bool RoleModel::insertRows(int row, int count, const QModelIndex &parent)
    {
        beginInsertRows(parent, row, row + count - 1);
        // FIXME: Implement me!
        endInsertRows();
        return true;
    }

    bool RoleModel::insertColumns(int column, int count, const QModelIndex &parent)
    {
        beginInsertColumns(parent, column, column + count - 1);
        // FIXME: Implement me!
        endInsertColumns();
        return true;
    }

    bool RoleModel::removeRows(int row, int count, const QModelIndex &parent)
    {
        beginRemoveRows(parent, row, row + count - 1);
        // FIXME: Implement me!
        endRemoveRows();
        return true;
    }

    bool RoleModel::removeColumns(int column, int count, const QModelIndex &parent)
    {
        beginRemoveColumns(parent, column, column + count - 1);
        // FIXME: Implement me!
        endRemoveColumns();
        return true;
    }

    void RoleModel::populateData(json lstRoleDto)
    {
        m_LstRoles.clear();
        for(size_t i = 0; i < lstRoleDto.size(); i += 1) {
            RoleDto roleDto;
            roleDto.FromJson(lstRoleDto[i]);
            m_LstRoles.push_back(roleDto);
        }
    }
}
