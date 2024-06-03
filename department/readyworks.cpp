#include "readyworks.h"
#include "ui_readyworks.h"
#include "departmentaccount.h"
#include "confirm.h"
#include <QCoreApplication>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>


ReadyWorks::ReadyWorks(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ReadyWorks)
{
    ui->setupUi(this);
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    openDatabases();
    loadData();
}

ReadyWorks::~ReadyWorks()
{
    delete ui;
}

void ReadyWorks::on_backButton_clicked()
{
    (new DepartmentAccount{})->show();
    this->close();
}

void ReadyWorks::openDatabases()
{
    dbWorks = QSqlDatabase::addDatabase("QSQLITE", "works_connection");
    dbWorks.setDatabaseName("mydatabase.db");

    if (!dbWorks.open()) {
        qDebug() << "Error: connection with additional_works.db failed";
    } else {
        qDebug() << "Database: connection with additional_works.db OK";
    }

    dbUsers = QSqlDatabase::addDatabase("QSQLITE", "users_connection");
    dbUsers.setDatabaseName("mydatabase.db");

    if (!dbUsers.open()) {
        qDebug() << "Error: connection with mydatabase.db failed";
    } else {
        qDebug() << "Database: connection with mydatabase.db OK";
    }
}

void ReadyWorks::loadData()
{
    if (!dbWorks.isOpen() || !dbUsers.isOpen()) {
        qDebug() << "Error: One or both databases are not open";
        return;
    }

    QSqlQuery worksQuery(dbWorks);
    if (!worksQuery.exec("SELECT id, name, user_id, start_date, deadline, workload, status, completion_date FROM additional_works WHERE status = 1 OR status = 2")) {
        qDebug() << "Error: Failed to query additional_works" << worksQuery.lastError().text();
        return;
    }


    // Установка заголовков таблицы
    ui->tableWidget->setRowCount(0);
    ui->tableWidget->setColumnCount(7);
    ui->tableWidget->setHorizontalHeaderLabels({"Наименование работы", "ФИО ответственного", "Дата начала", "Срок", "Сложность", "Статус", "Дата окончания"});

    // Повторный запрос для заполнения таблицы
    worksQuery.exec(); // Выполняем запрос заново

    // Заполнение таблицы
    int row = 0;
    QSet<int> addedUsers;

    while (worksQuery.next()) {
        QString workName = worksQuery.value(1).toString();
        int user_id = worksQuery.value(2).toInt();
        QString startDate = worksQuery.value(3).toString();
        QString deadline = worksQuery.value(4).toString();
        QString workload = worksQuery.value(5).toString();
        int status = worksQuery.value(6).toInt(); // Получение статуса
        QString completionDate = worksQuery.value(7).toString(); // Получение даты окончания

        if (addedUsers.contains(user_id)) {
            continue;
        }
        addedUsers.insert(user_id);

        QSqlQuery userQuery(dbUsers);
        userQuery.prepare("SELECT lastname, firstname, middlename FROM users WHERE id = :user_id");
        userQuery.bindValue(":user_id", user_id);
        if (!userQuery.exec() || !userQuery.next()) {
            qDebug() << "Error: Failed to query users for user_id" << user_id << userQuery.lastError().text();
            return;
        }

        QString lastname = userQuery.value(0).toString();
        QString firstname = userQuery.value(1).toString();
        QString middlename = userQuery.value(2).toString();
        QString fio = lastname + " " + firstname + " " + middlename;

        ui->tableWidget->insertRow(row);

        QString statusStr;
        switch (status) {
            case 0: statusStr = "В работе"; break;
            case 1: statusStr = "На проверке"; break;
            case 2: statusStr = "Принято"; break;
            case 3: statusStr = "Отклонено"; break;
        }


        ui->tableWidget->setItem(row, 0, new QTableWidgetItem(workName));
        ui->tableWidget->setItem(row, 1, new QTableWidgetItem(fio));
        ui->tableWidget->setItem(row, 2, new QTableWidgetItem(startDate));
        ui->tableWidget->setItem(row, 3, new QTableWidgetItem(deadline));
        ui->tableWidget->setItem(row, 4, new QTableWidgetItem(workload));
        ui->tableWidget->setItem(row, 5, new QTableWidgetItem(statusStr)); // Установка статуса
        ui->tableWidget->setItem(row, 6, new QTableWidgetItem(completionDate)); // Установка даты окончания

        row++;
    }
}

int ReadyWorks::getSelectedWorkId()
{
    int row = ui->tableWidget->currentRow();
    if (row < 0) {
        return -1;
    }
    QTableWidgetItem *item = ui->tableWidget->item(row, 0); // ID работы сохранен в первой колонке в UserRole
    if (!item) {
        return -1;
    }
    return item->data(Qt::UserRole).toInt();
}

void ReadyWorks::on_confirmButton_clicked()
{
    confirm *confirmWindow = new confirm();
    confirmWindow->show();
    this->close();
}

