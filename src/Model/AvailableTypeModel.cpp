#include "Model/AvailableTypeModel.h"

namespace Model {
    AvailableTypeModel::AvailableTypeModel(QObject *parent) : QAbstractItemModel(parent)
    {

    }

    QVariant AvailableTypeModel::headerData(int section, Qt::Orientation orientation, int role) const
    {
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

    QModelIndex AvailableTypeModel::index(int row, int column, const QModelIndex &parent) const
    {
        return hasIndex(row, column, parent) ? createIndex(row, column) : QModelIndex();
    }

    QModelIndex AvailableTypeModel::parent(const QModelIndex &index) const
    {
        return QModelIndex();
    }

    int AvailableTypeModel::rowCount(const QModelIndex &parent) const
    {
        Q_UNUSED(parent);

        return m_LstAvailableType.size();
    }

    int AvailableTypeModel::columnCount(const QModelIndex &parent) const
    {
        Q_UNUSED(parent);

        return 4;
    }

    QVariant AvailableTypeModel::data(const QModelIndex &index, int role) const
    {
        if (!index.isValid() || role != Qt::DisplayRole) {
            return QVariant();
        }

        if(index.column() == 0) {
            return QString::fromStdString(m_LstAvailableType.at(index.row()).getId());
        } else if(index.column() == 1) {
            return QString::fromStdString(m_LstAvailableType.at(index.row()).getName());
        } else if(index.column() == 2) {
            return QString::fromStdString(m_LstAvailableType.at(index.row()).getDescription());
        } else if(index.column() == 3) {
            return m_LstAvailableType.at(index.row()).isActive() ? "Active" : "Inactive";
        }
    }

    void AvailableTypeModel::populateData(const json &lstAvailableType)
    {
        m_LstAvailableType.clear();
        for(size_t i = 0; i < lstAvailableType.size(); i += 1) {
            AvailableTypeDto typeDto;
            typeDto.FromJson(lstAvailableType[i]);
            m_LstAvailableType.push_back(typeDto);
        }
    }
}
