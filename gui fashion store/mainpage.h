#ifndef MAINPAGE_H
#define MAINPAGE_H

#include <QMainWindow>

namespace Ui {
class Mainpage;
}

class Mainpage : public QMainWindow
{
    Q_OBJECT

public:
    explicit Mainpage(QWidget *parent = nullptr);
    ~Mainpage();

private slots:
    void on_pushButton_back_clicked();

private:
    Ui::Mainpage *ui;
};

#endif // MAINPAGE_H
