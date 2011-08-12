#include "MainWindow.h"
#include "ui_MainWindow.h"

#include <QTimer>
#include <QDebug>


extern "C" {
#include <mkdio.h>
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateMkd()));
    timer->start(500);
}

MainWindow::~MainWindow()
{
    delete ui;
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
    this->ui->textBrowser_2->setHtml(QString::fromLocal8Bit(out));
 #endif
    this->ui->textBrowser->setPlainText(QString::fromAscii(in));
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
