#include "employeeaccount.h"
#include "ui_employeeaccount.h"
#include "mainwindow.h"

employeeaccount::employeeaccount(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::employeeaccount)
{
    ui->setupUi(this);
}

employeeaccount::~employeeaccount()
{
    delete ui;
}

void employeeaccount::on_exit_clicked()
{
    (new QMainWindow{})->show();
    this->close();
}

