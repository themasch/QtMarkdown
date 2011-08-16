#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();


private slots:
    void updateMkd();
    void on_actionRefresh_2_triggered();
    void on_pushButton_clicked();
    void on_actionHide_Debug_triggered();
    void openFile();
    void saveFile();

private:
    Ui::MainWindow *ui;
    void initToolbar(QToolBar*);
};

#endif // MAINWINDOW_H
