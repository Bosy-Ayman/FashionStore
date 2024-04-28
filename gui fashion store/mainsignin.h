#ifndef MAINSIGNIN_H
#define MAINSIGNIN_H

#include <QMainWindow>
#include<QMessageBox>

namespace Ui {
class Mainsignin;
}

class Mainsignin : public QMainWindow
{
    Q_OBJECT

public:
    explicit Mainsignin(QWidget *parent = nullptr);
    ~Mainsignin();

private slots:
    void on_pushButton_cancel2_clicked();

    void on_pushButton_confirm_clicked();
    void isValidEmail(QString email);
    void isValidPassword(QString email);

    void on_pushButton_back_to_mainwindow_clicked();

    void on_checkBox_rules_stateChanged(int arg1);

private:
    Ui::Mainsignin *ui;
};

#endif // MAINSIGNIN_H
