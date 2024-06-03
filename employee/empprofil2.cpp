#include "empprofil2.h"
#include "ui_empprofil2.h"
#include <QDebug>
#include "empaccount.h"

empprofil2::empprofil2(const QString &login, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::empprofil2),
    m_login(login)
{
    ui->setupUi(this);

}

empprofil2::~empprofil2()
{
    delete ui;
}

void empprofil2::setData(const QString &lastname, const QString &firstname, const QString &middlename, const QString &academic_degree, const QString &academic_title)
{
    ui->lastnameEdit->setText(lastname);
    ui->lastnameEdit->setReadOnly(true);

    ui->firstnameEdit->setText(firstname);
    ui->firstnameEdit->setReadOnly(true);

    ui->patronicEdit->setText(middlename);
    ui->patronicEdit->setReadOnly(true);

    ui->academicdegreeEdit->setText(academic_degree);
    ui->academicdegreeEdit->setReadOnly(true);

    ui->academictitleEdit->setText(academic_title);
    ui->academictitleEdit->setReadOnly(true);
}

void empprofil2::on_backButton_clicked()
{
    empaccount *empAcc = new empaccount(m_login); // Передаем текущий логин
    empAcc->show();
    this->close();
}

