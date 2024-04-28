#include "mainsignin.h"
#include "ui_mainsignin.h"
#include "mainwindow.h"

Mainsignin::Mainsignin(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Mainsignin)
{
    ui->setupUi(this);
}

Mainsignin::~Mainsignin()
{
    delete ui;
}

void Mainsignin::on_pushButton_cancel2_clicked()
{

    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Are you sure you want to close the application?", "This will close the application. Are you sure?", QMessageBox::Yes | QMessageBox::No);
    if (reply == QMessageBox::Yes) {
        QApplication::quit();
    }
}



void Mainsignin::on_pushButton_confirm_clicked()
{
    if (!ui->checkBox_rules->isChecked()) {
        QMessageBox::information(this, "Error", "Please accept the terms and conditions.");
        return;
    }

    QString email = ui->lineEdit_email->text();
    QString Password = ui->lineEdit_password->text();
    if (email.contains(QRegularExpression("@gmail\\.com$", QRegularExpression::CaseInsensitiveOption)) && Password.length() > 8) {
        // email and password are valid
        QMessageBox::information(this, "Sign In Success", "You have successfully signed in.");

        MainWindow *mainpage = new MainWindow();
        this->hide();
        mainpage->show();

    } else if (!(email.contains(QRegularExpression("@gmail\\.com$"))) && !(Password.length() > 8)) {
        QMessageBox::warning(this, "Error", "Email and Password are incorrect, please enter a password that exceeds 8 characters and a valid email");

    } else if (!(Password.length() > 8)) {
        QMessageBox::warning(this, "Error", "The password is incorrect, please enter a password that exceeds 8 characters");

    } else if((!(email.contains(QRegularExpression("@gmail\\.com$"))))){
        QMessageBox::warning(this, "Error", "The email is incorrect");
    }else {
        QMessageBox::warning(this, "Error", "you didn't enter your name ");

        }
}

void Mainsignin::on_pushButton_back_to_mainwindow_clicked()
{
    MainWindow *mainpage = new MainWindow();
    this->hide();
    mainpage->show();
}


void Mainsignin::on_checkBox_rules_stateChanged(int arg1)
{


}
