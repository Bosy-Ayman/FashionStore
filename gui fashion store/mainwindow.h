
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include<QMessageBox>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow

{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_login_clicked();

    void on_pushButton_cancel1_clicked();


    void on_pushButton_sign_in_clicked();

    void on_pushButton_sign_in1_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
