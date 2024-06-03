#include "users.h"
#include "ui_users.h"
#include "admaccount.h"
#include "adminadd.h"
#include "usersdelete.h"

#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include "databasemanager.h"

users::users(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::users)
{
    ui->setupUi(this);
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);

    loadData();//
}

users::~users()
{
    delete ui;
}


void users::on_backButton_clicked()
{
    (new admaccount{})->show();
    this->close();
}


void users::on_addButton_clicked()
{
    (new AdminAdd{})->show();
    this->close();
}


void users::on_deleteButton_clicked()
{
    (new UsersDelete{})->show();
    this->close();
}

void users::loadData()
{
    DatabaseManager dbManager;

    if (!dbManager.openDatabase("mydatabase.db")) {
        qDebug() << "Failed to open database";
        return;
    }

    QSqlQuery query("SELECT lastname, firstname, middlename, role, position FROM users");

    if (!query.exec()) {
        qDebug() << "Error: Failed to execute query" << query.lastError().text();
        return;
    }

    ui->tableWidget->setRowCount(0); // Сбрасываем таблицу
    int row = 0;

    while (query.next()) {
        ui->tableWidget->insertRow(row);

        QString lastname = query.value(0).toString();
        QString firstname = query.value(1).toString();
        QString middlename = query.value(2).toString();
        int role = query.value(3).toInt();
        QString position = query.value(4).toString();

        QString roleStr;
        switch (role) {
            case 0: roleStr = "Администратор"; break;
            case 1: roleStr = position; break; // Используем должность для role = 1
            case 2: roleStr = "Преподаватель"; break;
            case 3: roleStr = "Представитель кафедры"; break;
            default: roleStr = "Неизвестно"; break;
        }

        ui->tableWidget->setItem(row, 0, new QTableWidgetItem(lastname));
        ui->tableWidget->setItem(row, 1, new QTableWidgetItem(firstname));
        ui->tableWidget->setItem(row, 2, new QTableWidgetItem(middlename));
        ui->tableWidget->setItem(row, 3, new QTableWidgetItem(roleStr));

        row++;
    }
}

