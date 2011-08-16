#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "Config.h"

#include <QTimer>
#include <QDebug>
#include <QIcon>
#include <QAction>

#include <QFileDialog>


extern "C" {
#include <mkdio.h>
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->ui->textBrowser_2->setVisible(false);
    this->showMaximized();

    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateMkd()));
    timer->start(500);

    this->initToolbar(this->ui->mainToolBar);
}

void MainWindow::initToolbar(QToolBar *toolBar)
{
    QAction *refresh = new QAction(QIcon::fromTheme("view-refresh"),  tr("&refresh"), this);
    QAction *open    = new QAction(QIcon::fromTheme("document-open"), tr("&open"),    this);
    QAction *save    = new QAction(QIcon::fromTheme("document-save"), tr("&save"),    this);
    QAction *newFile = new QAction(QIcon::fromTheme("document-new"),  tr("&new"),     this);

    toolBar->addAction(open);
    toolBar->addAction(save);
    toolBar->addAction(newFile);
    toolBar->addAction(refresh);

    connect(open, SIGNAL(triggered()), this, SLOT(openFile()));

    connect(save, SIGNAL(triggered()), this, SLOT(saveFile()));

#ifdef DEBUG
    QAction *tglDebug = new QAction("debug", this);
    toolBar->addAction(tglDebug);
    // connect
    connect(tglDebug, SIGNAL(triggered()), this, SLOT(on_actionHide_Debug_triggered()));
#endif
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::openFile()
{
    QString path = QFileDialog::getOpenFileName(this, "Datei öffnen", QDir::homePath());
    if(!(path.isNull() || path.isEmpty())) {
        QFile fp(path);
        fp.open(QFile::ReadOnly);
        this->ui->plainTextEdit->setPlainText(QString::fromLocal8Bit(fp.readAll()));
    } else {
        qDebug() << path;
    }

}

void MainWindow::saveFile()
{
    QString path = QFileDialog::getSaveFileName(this, "Datei speichern", QDir::homePath());
    if(!(path.isNull() || path.isEmpty())) {
        QFile fp(path);
        fp.open(QFile::WriteOnly | QFile::Truncate);
        QString text = this->ui->plainTextEdit->toPlainText();
        fp.write(text.toLocal8Bit());
    } else {
        qDebug() << path;
    }
}

void MainWindow::updateMkd()
{
    QString input = this->ui->plainTextEdit->toPlainText();
    char *in = strdup(input.toAscii().data());
 #ifdef _MKDIO_D
    MMIOT *mkd = mkd_string(in, input.length(), MKD_AUTOLINK);
    mkd_compile(mkd, MKD_AUTOLINK);
    char *out = NULL;
    mkd_document(mkd, &out);
    this->ui->textBrowser->setHtml(QString::fromLocal8Bit(out));
 #endif
    this->ui->textBrowser_2->setPlainText(QString::fromAscii(in)); // DEBUG
    free(in);
}

void MainWindow::on_actionRefresh_2_triggered()
{
    this->updateMkd();
}

void MainWindow::on_pushButton_clicked()
{
    this->updateMkd();
}

void MainWindow::on_actionHide_Debug_triggered()
{
    this->ui->textBrowser_2->setVisible(!this->ui->textBrowser_2->isVisible());
}
