#include "usersdelete.h"
#include "ui_usersdelete.h"
#include "users.h"
#include "databasemanager.h"

#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QMessageBox>

UsersDelete::UsersDelete(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::UsersDelete)
{
    ui->setupUi(this);
}

UsersDelete::~UsersDelete()
{
    delete ui;
}

void UsersDelete::on_confirmButton_clicked()
{
    QString lastname = ui->Last_name->text();
       QString firstname = ui->First_name->text();
       QString middlename = ui->Patronic_name->text();
       QString login = ui->Login->text();

       DatabaseManager dbManager;
       if (dbManager.openDatabase("mydatabase.db")) {
           QSqlQuery query;
           query.prepare("DELETE FROM users WHERE lastname = :lastname AND firstname = :firstname AND middlename = :middlename AND login = :login");
           query.bindValue(":lastname", lastname);
           query.bindValue(":firstname", firstname);
           query.bindValue(":middlename", middlename);
           query.bindValue(":login", login);

           if (query.exec()) {
               if (query.numRowsAffected() > 0) {
                   qDebug() << "Пользователь удалён";
                   QMessageBox::information(this, "Success", "Пользователь удалён.");
               } else {
                   qDebug() << "No user found with the provided details";
                   QMessageBox::warning(this, "Error", "No user found with the provided details.");
               }
               this->close();
               users *usersWindow = new users();
               usersWindow->show();
           } else {
               qDebug() << "Error: Failed to delete user" << query.lastError().text();
               QMessageBox::critical(this, "Error", "Failed to delete user.");
           }
       } else {
           qDebug() << "Failed to open database";
           QMessageBox::critical(this, "Error", "Failed to open database.");
       }
}


void UsersDelete::on_backButton_clicked()
{
    (new users{})->show();
    this->close();
}
