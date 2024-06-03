#include "addteacher.h"
#include "ui_addteacher.h"
#include "users.h"
#include "databasemanager.h"

#include <QDebug>
#include <QMessageBox>


addteacher::addteacher(const QString &login, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::addteacher),
    m_login(login) // Инициализация логина пользователя
{
    ui->setupUi(this);
}

addteacher::~addteacher()
{
    delete ui;
}

void addteacher::on_pushButton_clicked()
{
    QString academicDegree = ui->comboBox->currentText();
    QString academicTitle = ui->comboBox_2->currentText();

        DatabaseManager dbManager;
        if (dbManager.openDatabase("mydatabase.db")) {
            QSqlQuery query;
            query.prepare("UPDATE users SET academic_degree = :academic_degree, academic_title = :academic_title WHERE login = :login");
            query.bindValue(":academic_degree", academicDegree);
            query.bindValue(":academic_title", academicTitle);
            query.bindValue(":login", m_login); // Используем логин для идентификации пользователя

            if (query.exec()) {
                qDebug() << "Academic details updated successfully";
                this->close();
                users *usersWindow = new users();
                usersWindow->show();
            } else {
                qDebug() << "Error: Failed to update academic details" << query.lastError().text();
            }
        } else {
            qDebug() << "Failed to open database";
        }
}

