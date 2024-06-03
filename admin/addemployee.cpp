#include "addemployee.h"
#include "ui_addemployee.h"
#include "users.h"
#include "databasemanager.h"

#include <QDebug>
#include <QMessageBox>

addemployee::addemployee(const QString &login, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::addemployee),
    m_login(login) // Инициализация логина пользователя
{
    ui->setupUi(this);
}

addemployee::~addemployee()
{
    delete ui;
}


void addemployee::on_pushButton_clicked()
{
    QString position = ui->comboBox->currentText();

        DatabaseManager dbManager;
        if (dbManager.openDatabase("mydatabase.db")) {
            QSqlQuery query;
            query.prepare("UPDATE users SET position = :position WHERE login = :login");
            query.bindValue(":position", position);
            query.bindValue(":login", m_login); // Используем логин для идентификации пользователя

            if (query.exec()) {
                qDebug() << "Position updated successfully";
                this->close();
                users *usersWindow = new users();
                usersWindow->show();
            } else {
                qDebug() << "Error: Failed to update position" << query.lastError().text();
            }
        } else {
            qDebug() << "Failed to open database";
        }
}

