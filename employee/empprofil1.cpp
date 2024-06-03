#include "empprofil1.h"
#include "ui_empprofil1.h"
#include <QDebug>
#include "empaccount.h"

empprofil1::empprofil1(const QString &login, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::empprofil1),
    m_login(login) // Инициализируем приватное поле логина
{
    ui->setupUi(this);

}

empprofil1::~empprofil1()
{
    delete ui;
}

void empprofil1::setData(const QString &lastname, const QString &firstname, const QString &middlename, const QString &position)
{
    ui->lastnameEdit->setText(lastname);
    ui->lastnameEdit->setReadOnly(true);

    ui->firstnameEdit->setText(firstname);
    ui->firstnameEdit->setReadOnly(true);

    ui->patronicEdit->setText(middlename);
    ui->patronicEdit->setReadOnly(true);

    ui->positionEdit->setText(position);
    ui->positionEdit->setReadOnly(true);
}

void empprofil1::on_backButton_clicked()
{
    empaccount *empAcc = new empaccount(m_login); // Передаем текущий логин
    empAcc->show();
    this->close();
}

