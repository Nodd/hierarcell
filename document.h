#ifndef DOCUMENT_H
#define DOCUMENT_H

#include <QObject>

#include "tabmodel.h"

class Document : public QObject
{
    Q_OBJECT
public:
    explicit Document(QObject *parent = nullptr);

    int numTabs();
    void addTab(int index);
    void removeTab(int index);
    TabModel *tabModel(int index);

private:
    QList<TabModel *> m_tabModels;

signals:
};

#endif // DOCUMENT_H
