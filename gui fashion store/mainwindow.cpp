
#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "mainpage.h"
#include "mainsignin.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_pushButton_login_clicked()
{
    QString email = ui->lineEdit_email->text();
    QString Password = ui->lineEdit_password->text();

    if (email =="administrator@gmail.com" && Password=="2023"){
        QMessageBox::information(this, "Login Success", "You have successfully logged in.");
        Mainpage *mainpage = new Mainpage();
        this->hide();
        mainpage->show();
    }else {
        QMessageBox::warning(this, "Login Failed", "Please enter a valid email and password.");
    }
}



void MainWindow::on_pushButton_cancel1_clicked()
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Are you sure you want to close the application?", "This will close the application. Are you sure?", QMessageBox::Yes | QMessageBox::No);
    if (reply == QMessageBox::Yes) {
        QApplication::quit();
    }
}



void MainWindow::on_pushButton_sign_in_clicked()
{
    Mainsignin *mainpage = new Mainsignin();
    this->hide();
    mainpage->show();
}


void MainWindow::on_pushButton_sign_in1_clicked()
{
    Mainsignin *mainpage = new Mainsignin();
    this->hide();
    mainpage->show();
}

