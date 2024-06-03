#include "listworks.h"
#include "ui_listworks.h"
#include "departmentaccount.h"
#include "confirm.h"
#include "addwork.h"

listWorks::listWorks(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::listWorks)
{
    ui->setupUi(this);
    openDatabases();
    loadData();
}

listWorks::~listWorks()
{
    delete ui;
}

void listWorks::openDatabases()
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

void listWorks::closeDatabases()
{
    if (dbWorks.isOpen()) {
        dbWorks.close();
    }

    if (dbUsers.isOpen()) {
        dbUsers.close();
    }
}

void listWorks::loadData()
{
    if (!dbWorks.isOpen() || !dbUsers.isOpen()) {
        qDebug() << "Error: One or both databases are not open";
        return;
    }

    QSqlQuery worksQuery(dbWorks);
    if (!worksQuery.exec("SELECT name, user_id, start_date, deadline, workload FROM additional_works WHERE status = 0 OR status = 1")) {
        qDebug() << "Error: Failed to query additional_works" << worksQuery.lastError().text();
        return;
    }

    ui->worksTable->setRowCount(0);
    ui->worksTable->setColumnCount(5);
    ui->worksTable->setHorizontalHeaderLabels({"Наименование работы", "ФИО ответственного", "Дата начала", "Срок", "Сложность"});

    int row = 0;
    QSet<int> addedUsers;

    while (worksQuery.next()) {
        QString workName = worksQuery.value(0).toString();
        int user_id = worksQuery.value(1).toInt();
        QString startDate = worksQuery.value(2).toString();
        QString deadline = worksQuery.value(3).toString();
        QString workload = worksQuery.value(4).toString();

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

        ui->worksTable->insertRow(row);
        ui->worksTable->setItem(row, 0, new QTableWidgetItem(workName));
        ui->worksTable->setItem(row, 1, new QTableWidgetItem(fio));
        ui->worksTable->setItem(row, 2, new QTableWidgetItem(startDate));
        ui->worksTable->setItem(row, 3, new QTableWidgetItem(deadline));
        ui->worksTable->setItem(row, 4, new QTableWidgetItem(workload));

        row++;
    }
}


void listWorks::on_backButton_clicked()
{
    (new DepartmentAccount{}) -> show();
    this -> close();
}


void listWorks::on_addButton_clicked()
{
    (new AddWork{})->show();
    this->close();
}

