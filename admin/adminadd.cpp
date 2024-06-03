#include "adminadd.h"
#include "ui_adminadd.h"
#include "users.h"
#include "addemployee.h"
#include "addteacher.h"

#include "QMessageBox"
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include "databasemanager.h"

AdminAdd::AdminAdd(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AdminAdd)
{
    ui->setupUi(this);
}

AdminAdd::~AdminAdd()
{
    delete ui;
}

void AdminAdd::on_backButton_clicked()
{
    (new users{})->show();
    this->close();
}



void AdminAdd::on_confirmButton_clicked()
{
    // Получение данных из всех полей ввода
    QString lastname = ui->Last_name->text();
    QString firstname = ui->First_name->text();
    QString middlename = ui->Patronic_name->text();
    QString login = ui->Login->text();
    QString password = ui->Password->text();
    int role = ui->rolecomboBox->currentIndex(); // Индекс выбранной роли

    // Проверка имени, фамилии и отчества на соответствие условиям
    QRegExp rx("^[А-ЯЁ][а-яё]*$"); // Регулярное выражение для проверки имени и фамилии
    QRegExp rxMiddlename("^[А-ЯЁ][а-яё]*$|^$"); // Регулярное выражение для проверки отчества или пустого поля
    QRegExp rxLoginPassword("^[A-Za-z0-9]+$"); // Регулярное выражение для проверки логина и пароля

    if (!rx.exactMatch(lastname) || !rx.exactMatch(firstname) || !rxMiddlename.exactMatch(middlename)) {
        // Вывод сообщения об ошибке
        QMessageBox::critical(this, "Ошибка", "ФИО должны состоять только из русских букв и начинаться с заглавной буквы (отчество может быть пустым)!");
        return; // Остановка выполнения функции
    }

    if (login.isEmpty() || password.isEmpty() || !rxLoginPassword.exactMatch(login) || !rxLoginPassword.exactMatch(password)) {
        // Вывод сообщения об ошибке
        QMessageBox::critical(this, "Ошибка", "Логин и пароль должны быть непустыми и содержать только английские буквы и цифры!");
        return; // Остановка выполнения функции
    }

    // Сохранение данных в базу данных в зависимости от выбранной роли
    DatabaseManager dbManager;
    if (dbManager.openDatabase("mydatabase.db")) {
        QSqlQuery query;
        query.prepare("INSERT INTO users (lastname, firstname, middlename, role, login, password, "
                      "academic_degree, academic_title, position) "
                      "VALUES (:lastname, :firstname, :middlename, :role, :login, :password, "
                      ":academic_degree, :academic_title, :position)");
        query.bindValue(":lastname", lastname);
        query.bindValue(":firstname", firstname);
        query.bindValue(":middlename", middlename);
        query.bindValue(":login", login);
        query.bindValue(":password", password);

        // Установка значений в зависимости от выбранной роли
        switch (role) {
            case 0: // Администратор
                query.bindValue(":role", 0);
                query.bindValue(":academic_degree", " ");
                query.bindValue(":academic_title", " ");
                query.bindValue(":position", " ");
                if (query.exec()) {
                    qDebug() << "User data inserted successfully";
                    // Открытие окна Users
                    users *usersWindow = new users();
                    usersWindow->show();
                    this->close(); // Закрыть окно AdminAdd
                } else {
                    qDebug() << "Error: Failed to insert user data" << query.lastError().text();
                }
                break;
            case 1: // Учебно-вспомогательный отдел
                query.bindValue(":role", 1);
                query.bindValue(":academic_degree", " ");
                query.bindValue(":academic_title", " ");
                if (query.exec()) {
                    qDebug() << "User data inserted successfully";
                    // Открытие окна addemployee
                    addemployee *addEmployeeWindow = new addemployee(login);
                    addEmployeeWindow->show();
                    this->close(); // Закрыть окно AdminAdd
                } else {
                    qDebug() << "Error: Failed to insert user data" << query.lastError().text();
                }
                break;
            case 2: // Преподаватель
                query.bindValue(":role", 2);
                query.bindValue(":position", " ");
                if (query.exec()) {
                    qDebug() << "User data inserted successfully";
                    // Открытие окна addteacher
                    addteacher *addTeacherWindow = new addteacher(login);
                    addTeacherWindow->show();
                    this->close(); // Закрыть окно AdminAdd
                } else {
                    qDebug() << "Error: Failed to insert user data" << query.lastError().text();
                }
                break;
            case 3: // Представитель кафедры
                query.bindValue(":role", 3);
                query.bindValue(":academic_degree", " ");
                query.bindValue(":academic_title", " ");
                query.bindValue(":position", " ");
                if (query.exec()) {
                    qDebug() << "User data inserted successfully";
                    // Открытие окна Users
                    users *usersWindow = new users();
                    usersWindow->show();
                    this->close(); // Закрыть окно AdminAdd
                } else {
                    qDebug() << "Error: Failed to insert user data" << query.lastError().text();
                }
                break;
            default:
                qDebug() << "Error: Invalid role selected";
                break;
        }
    } else {
        qDebug() << "Failed to open database";
    }
}
