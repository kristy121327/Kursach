#include "empaccount.h"
#include "ui_empaccount.h"
#include "mainwindow.h"
#include "newworks.h"

#include "empprofil1.h"
#include "empprofil2.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include "QMessageBox"


empaccount::empaccount(const QString &login, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::empaccount),
    m_login(login) // Инициализируем приватное поле логина
{
    ui->setupUi(this);
}

empaccount::~empaccount()
{
    delete ui;
}

void empaccount::on_exit_clicked()
{
    MainWindow *loginWindow = new MainWindow();
    loginWindow->show();
    this->close();
}


void empaccount::on_newworkButton_clicked()
{
    newworks *worksWindow = new newworks(m_login);
    worksWindow->show();
    this->close();
}


void empaccount::on_accountButton_clicked()
{
    // Открываем базу данных
       DatabaseManager dbManager;
       if (dbManager.openDatabase("mydatabase.db")) {
           QSqlQuery query;
           query.prepare("SELECT role, lastname, firstname, middlename, academic_degree, academic_title, position FROM users WHERE login = :login");
           query.bindValue(":login", m_login);

           if (query.exec() && query.next()) {
               int role = query.value(0).toInt();
               QString lastname = query.value(1).toString();
               QString firstname = query.value(2).toString();
               QString middlename = query.value(3).toString();
               QString academic_degree = query.value(4).toString();
               QString academic_title = query.value(5).toString();
               QString position = query.value(6).toString();

               // Проверяем роль пользователя и открываем соответствующее окно
               if (role == 1) {
                   // Открываем окно empprofil1
                   empprofil1 *empProfile1 = new empprofil1(m_login);
                   empProfile1->setData(lastname, firstname, middlename, position);
                   empProfile1->show();
                   this->close();
               } else if (role == 2) {
                   // Открываем окно empprofil2
                   empprofil2 *empProfile2 = new empprofil2(m_login);
                   empProfile2->setData(lastname, firstname, middlename, academic_degree, academic_title);
                   empProfile2->show();
                   this->close();
               } else {
                   // Если роль не определена, выведите сообщение об ошибке
                   QMessageBox::critical(this, "Ошибка", "Неверная роль пользователя");
               }
           } else {
               // Если запрос к базе данных не вернул результат, выведите сообщение об ошибке
               QMessageBox::critical(this, "Ошибка", "Не удалось получить информацию о пользователе");
           }
       } else {
           // Если не удалось открыть базу данных, выведите сообщение об ошибке
           qDebug() << "Failed to open database";
       }

}

