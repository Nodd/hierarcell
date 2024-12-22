#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTabBar>

#include "document.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QTabBar *m_tabBar;
    Document *m_document;

    QTabBar *createTabBar();
    void connect();

private slots:
    void on_tabChanged(int index);
    void on_actionIndent_triggered(bool checked);
    void on_actionUnindent_triggered(bool checked);
    int newTab();
};
#endif // MAINWINDOW_H
