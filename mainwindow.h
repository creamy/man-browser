#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QModelIndex>
#include <QtWebKit/QWebView>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);

    ~MainWindow();
    
private:
    Ui::MainWindow *ui;
    QWebView *view;

private slots:
    void changeCurrent(const QModelIndex &current);
};

#endif // MAINWINDOW_H
