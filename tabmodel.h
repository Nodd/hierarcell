#ifndef TABMODEL_H
#define TABMODEL_H

#include <QObject>
#include <QStandardItemModel>

class TabModel : public QStandardItemModel
{
public:
    TabModel();
    static TabModel *newEmpty();

private:
    QString m_name;

private slots:
    void on_itemChanged(QStandardItem *item);
};

#endif // TABMODEL_H
