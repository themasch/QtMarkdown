#include "MainWindow.h"
#include "ui_MainWindow.h"

#include <QTimer>
#include <QDebug>

#include <string.h>
#include <iostream>

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
    timer->start(2000);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateMkd()
{
    QString input = this->ui->plainTextEdit->toPlainText();
    char *in = input.toLocal8Bit().data();
    MMIOT *mkd = mkd_string(in, input.length(), MKD_AUTOLINK);
    int status = mkd_compile(mkd, MKD_AUTOLINK);
    char *out = NULL;
    int count = mkd_document(mkd, &out);
    this->ui->textBrowser->setHtml(out);
}
