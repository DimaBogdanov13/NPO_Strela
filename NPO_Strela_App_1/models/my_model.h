#ifndef MY_MODEL_H
#define MY_MODEL_H

#include <QAbstractListModel>

#include <QPair>
#include <QList>

class My_Model : public QAbstractListModel
{
    Q_OBJECT

public:

    explicit My_Model(QObject *parent = nullptr);

    enum Roles {
        nameRole = Qt::UserRole + 1,
        progressRole = Qt::UserRole + 2,

       };

    QVariant data(const QModelIndex &index, int role) const;

    QHash<int, QByteArray> roleNames() const;

    int rowCount(const QModelIndex &parent = QModelIndex()) const;

    Q_INVOKABLE void add_Item(QPair<float, float> value);

    Q_INVOKABLE QVariantMap get(int row) const;

    void update_Progress(int row, float value);



private:

    QList<QPair<float, float>> m_List;

    QByteArray name = "name",
            progress = "progress";

signals:

   void myModel_Changed();
};

#endif // MY_MODEL_H
