#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QTreeView>

#include <iostream>
#include <set>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    std::cout << "start" << std::endl;
    ui->setupUi(this);
    m_tabBar = createTabBar();
    m_document = new Document();

    newTab();
}

MainWindow::~MainWindow()
{
    delete m_document;
    delete m_tabBar;
    delete ui;
}

QTabBar *MainWindow::createTabBar()
{
    // Create and configure the tab bar
    QTabBar *tabBar = new QTabBar();
    tabBar->setShape(QTabBar::RoundedSouth);
    tabBar->setExpanding(false);
    tabBar->setTabsClosable(true);
    // m_tabBar->setMovable(true);
    ui->centralLayout->addWidget(tabBar);

    // Add a tab that act as a new tab button
    tabBar->addTab(QIcon::fromTheme(QIcon::ThemeIcon::ListAdd), "");
    tabBar->setTabButton(0, QTabBar::RightSide, nullptr);

    QObject::connect(tabBar, &QTabBar::currentChanged, this, &MainWindow::on_tabChanged);

    return tabBar;
}

void MainWindow::connect()
{
    QObject::connect(ui->actionNew_Tab, &QAction::triggered, this, &MainWindow::newTab);
    QObject::connect(ui->actionIndent,
                     &QAction::triggered,
                     this,
                     &MainWindow::on_actionIndent_triggered);
    QObject::connect(ui->actionUnindent,
                     &QAction::triggered,
                     this,
                     &MainWindow::on_actionUnindent_triggered);
}

void MainWindow::on_tabChanged(int index)
{
    int nb_tabs = m_tabBar->count();
    // Check that the index is valid
    if (index < 0 || index >= nb_tabs) {
        return;
    }

    // Create a new tab if the + tab is activated
    if (index == nb_tabs - 1) {
        newTab();
        return;
    }

    // Otherwise, load the tab data
    ui->tableView->setModel(m_document->tabModel(index));
}

void MainWindow::on_actionIndent_triggered(bool checked)
{
    qDebug() << "on_actionIndent_triggered";
    QItemSelectionModel *selection = ui->tableView->selectionModel();
    QModelIndexList indexes = selection->selectedIndexes();

    std::set<int> rows{};
    for (auto index = indexes.cbegin(), end = indexes.cend(); index != end; ++index) {
        std::cout << index->row() << std::endl;
        rows.insert(index->row());
    }

    // Check if the row indexes are continuous
    std::cout << *rows.rbegin() << " " << *rows.begin() << " " << rows.size() << std::endl;
    if (*rows.rbegin() - *rows.begin() != rows.size() - 1) {
        std::cout << "non contiguous" << std::endl;
        return;
    }
}
void MainWindow::on_actionUnindent_triggered(bool checked) {}

int MainWindow::newTab()
{
    int index = m_tabBar->count() - 1;
    m_document->addTab(index);
    m_tabBar->insertTab(index, QString(tr("Tab %1")).arg(index + 1));
    m_tabBar->setCurrentIndex(index);
    return index;
}
