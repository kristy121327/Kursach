#include "admaccount.h"
#include "ui_admaccount.h"
#include "mainwindow.h"
#include "users.h"

admaccount::admaccount(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::admaccount)
{
    ui->setupUi(this);

}

admaccount::~admaccount()
{
    delete ui;
}

void admaccount::on_exit_batton_clicked()
{
    MainWindow *loginWindow = new MainWindow();
    loginWindow->show();
    this->close();
}


void admaccount::on_pushButton_clicked()
{
    (new users{})->show();
    this->close();
}

