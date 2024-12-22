#include "document.h"

Document::Document(QObject *parent)
    : QObject{parent}
{}

int Document::numTabs()
{
    return m_tabModels.count();
}

void Document::addTab(int index)
{
    TabModel *tabModel = new TabModel();
    m_tabModels.insert(index, tabModel);
}

void Document::removeTab(int index)
{
    TabModel *tabModel = m_tabModels.takeAt(index);
    delete tabModel;
}

TabModel *Document::tabModel(int index)
{
    return m_tabModels[index];
}
