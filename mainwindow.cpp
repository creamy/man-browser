/*

  man browser

  by Waitman Gobble
  NO WARRANTIES

  This QT application displays your filesystem in a tree view on the left side of the window.
  When you click on a file in the tree view the corresponding man page (if any) is displayed in the right view.

  */

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileSystemModel>
#include <QSplitter>
#include <QListView>
#include <QTextEdit>
#include <QTreeView>
#include <QtWebKit/QWebView>
#include <QProcess>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QSplitter *splitter = new QSplitter(ui->centralWidget);

    QTreeView *tree = new QTreeView;

    view = new QWebView(ui->centralWidget);
    view->setHtml("<HTML><BODY STYLE='background-color:#000;color:#00ff00;'><style type='text/css'>pre { font-size:140%; }</style><H1>:: man browser ::</H1><pre>by Waitman Gobble\nSan Jose, California USA\n<a href='mailto:waitman@waitman.net'>waitman@waitman.net</a>\nTo Speak Press +1.650.396.7580\n\nNO WARRANTIES</pre></BODY></HTML>");
    view->show();

    splitter->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    splitter->addWidget(tree);
    splitter->addWidget(view);

    QFileSystemModel *model = new QFileSystemModel;
       model->setRootPath(QDir::currentPath());
       model->sort(2,Qt::AscendingOrder);

       tree->setModel(model);
          tree->setAnimated(false);
          tree->setSortingEnabled(true);
          tree->sortByColumn(2, Qt::AscendingOrder);
          tree->setColumnWidth(0, 250);
          tree->setSelectionMode(QAbstractItemView::SingleSelection);
          connect(tree, SIGNAL(clicked(QModelIndex)), this, SLOT(changeCurrent(QModelIndex)));

    setCentralWidget(splitter);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::changeCurrent(const QModelIndex &current)
 {

    QString text = current.data(Qt::DisplayRole).toString();
    statusBar()->showMessage(
    tr("man browser (%1) ")
        .arg(text));

    QStringList arguments;

    //http://www.oac.uci.edu/indiv/ehood/man2html.html
    QString foo = "/usr/bin/man "+text+" | /usr/local/bin/man2html ";

    arguments << "-c" << foo;

    QProcess* process = new QProcess(this);
    process->start("/bin/sh", arguments);
    process->waitForFinished();
    QString tmp = process->readAll();

    QString out = tmp.replace("<BODY>","<BODY STYLE='background-color:#000;color:#00ff00;'><style type='text/css'>pre { font-size:140%; }</style><H1>:: "+text+" ::</H1>");

    view->setHtml(out);

 }
