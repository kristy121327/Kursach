#include "departmentaccount.h"
#include "ui_departmentaccount.h"
#include "mainwindow.h"
#include "listworks.h"
#include "addwork.h"
#include "readyworks.h"

DepartmentAccount::DepartmentAccount(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DepartmentAccount)
{
    ui->setupUi(this);
}

DepartmentAccount::~DepartmentAccount()
{
    delete ui;
}


void DepartmentAccount::on_exitButton_clicked()
{
    MainWindow *loginWindow = new MainWindow();
    loginWindow->show();
    this->close();
}

void DepartmentAccount::on_NewWorksButton_clicked()
{
    (new listWorks{})->show();
    this->close();
}

void DepartmentAccount::on_ConfirmWorksButton_2_clicked()
{
    (new ReadyWorks{})->show();
    this->close();
}

