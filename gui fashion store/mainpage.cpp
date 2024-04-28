#include "mainpage.h"
#include "ui_mainpage.h"
#include "mainwindow.h"

Mainpage::Mainpage(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Mainpage)
{
    ui->setupUi(this);
}

Mainpage::~Mainpage()
{
    delete ui;
}

void Mainpage::on_pushButton_back_clicked()
{
    MainWindow *mainpage = new MainWindow();
    this->hide();
    mainpage->show();
}

