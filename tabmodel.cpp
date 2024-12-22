#include "tabmodel.h"

#include <QStandardItem>

TabModel::TabModel()
{
    QStandardItem item = QStandardItem("");
    appendRow(&item);

    QObject::connect(this, &QStandardItemModel::itemChanged, this, &TabModel::on_itemChanged);
}

TabModel *TabModel::newEmpty()
{
    TabModel *tabModel = new TabModel();
    QStandardItem parentItem = QStandardItem();
    QStandardItem childItem = QStandardItem();
    parentItem.setChild(0, &childItem);
    tabModel->appendRow(&parentItem);
    return tabModel;
}

void TabModel::on_itemChanged(QStandardItem *item)
{
    // No action if the item is empty
    if (item->text() == "") {
        // TODO: Remove empty rows if multiple at the bottom
        return;
    }

    // Get parent item
    QStandardItem *parent = item->parent();
    if (parent == nullptr) {
        parent = invisibleRootItem();
    }

    // Ensure that there is always an empty row at the end
    if (item->row() == parent->rowCount() - 1) {
        parent->setRowCount(parent->rowCount() + 1);
    }

    // Ensure that there is always an empty column at the end
    if (item->column() == parent->columnCount() - 1) {
        parent->setColumnCount(parent->columnCount() + 1);
    }
}
