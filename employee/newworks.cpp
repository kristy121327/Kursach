#include "newworks.h"
#include "ui_newworks.h"
#include "empaccount.h"
#include "qmessagebox.h"
#include "confirmwork.h"

#include "databasemanager.h"
#include "worksdatamanager.h"
#include "mainwindow.h"
#include <QCoreApplication>
#include <QDebug>

newworks::newworks(const QString &login, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::newworks),
    m_login(login) // Инициализируем логин
{
    ui->setupUi(this);
    populateWorksTableForUser(); // Заполнение таблицы при создании окна ДОБАВИЛА
}

newworks::~newworks()
{
    delete ui;
}

void newworks::on_backButton_clicked()
{
    empaccount *accountWindow = new empaccount(m_login); // Передаем логин в empaccount
    accountWindow->show();
    this->close();
}


void newworks::on_confirmButton_clicked()
{
    (new confirmwork{m_login})->show();
    this->close();
}

void newworks::populateWorksTableForUser() //ДОБАВИЛА
{
    WorksDataManager dbworkdatamanager;
    DatabaseManager dbManager;


    if (!dbworkdatamanager.openDatabase("mydatabase.db")) {
        qDebug() << "Failed to open database";
        return;
    }


    // Получаем имя текущего пользователя
    QString currentUser = m_login;
    qDebug() << "!!Current user:" << currentUser;

    // Фильтрация данных для конкретного пользователя
    QSqlQuery query;
    query.prepare("SELECT name, workload, deadline, status, payment, comment "
                  "FROM additional_works "
                  "JOIN users ON user_id = users.id WHERE users.login = :username;"
                  );
    query.bindValue(":username", currentUser);
    if (!query.exec()) {
        qDebug() << query.lastError().text();
        return;
    }

    // Очистка содержимого таблицы
    ui->worksTable->clearContents();
    ui->worksTable->setRowCount(0);

    int row = 0;
    while (query.next()) {

        // Вставка данных в таблицу
        ui->worksTable->insertRow(row);

        int status = query.value(3).toInt();

        QString statusStr;
        switch (status) {
            case 0: statusStr = "В работе"; break;
            case 1: statusStr = "На проверке"; break;
            case 2: statusStr = "Принято"; break;
            case 3: statusStr = "Отклонено"; break;
        }

        ui->worksTable->setItem(row, 0, new QTableWidgetItem(query.value(0).toString())); // Наименование
        ui->worksTable->setItem(row, 1, new QTableWidgetItem(query.value(1).toString())); // Сложность
        ui->worksTable->setItem(row, 2, new QTableWidgetItem(query.value(2).toString())); // Срок
        ui->worksTable->setItem(row, 3, new QTableWidgetItem(statusStr));                 // Статус
        ui->worksTable->setItem(row, 4, new QTableWidgetItem(query.value(4).toString())); // Оплата
        ui->worksTable->setItem(row, 5, new QTableWidgetItem(query.value(5).toString())); // Комментарий

        row++;
    }
    ui->worksTable->repaint();
}
