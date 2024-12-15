#include "my_model.h"

My_Model::My_Model(QObject *parent) : QAbstractListModel(parent)
{
    connect(this, &QAbstractListModel::dataChanged, this, &My_Model::myModel_Changed);

}

QVariant My_Model::data(const QModelIndex &index, int role) const {

    QVariant answer;

    switch (role) {

    case nameRole:

        answer = m_List.at(index.row()).first;

        break;

    case progressRole:

        answer = m_List.at(index.row()).second;

        break;
    }

    return answer;
}

QHash<int, QByteArray> My_Model::roleNames() const {

    QHash<int, QByteArray> roles {

        {nameRole, name},
        {progressRole, progress}


    };

    return roles;
}

int My_Model::rowCount(const QModelIndex &parent) const {

    Q_UNUSED(parent)
    return m_List.count();
}

void My_Model::add_Item(QPair<float, float> value){

    beginInsertRows(QModelIndex(), rowCount(), rowCount());

    m_List.append(value);

    endInsertRows();
}

QVariantMap My_Model::get(int row) const {

    return {
        {name, m_List.at(row).first},
        {progress, m_List.at(row).second}


    };
}

void My_Model::update_Progress(int row, float value){

    m_List[row].second = value;

    QModelIndex index = createIndex(row,0);

    emit dataChanged(index, index);

}
