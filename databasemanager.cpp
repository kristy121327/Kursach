#include "databasemanager.h"
#include <QDebug>

DatabaseManager::DatabaseManager(QObject *parent) : QObject(parent)
{
}

DatabaseManager::~DatabaseManager()
{
    closeDatabase();
}

bool DatabaseManager::openDatabase(const QString &dbName) const
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(dbName);

    if (!db.open()) {
        qDebug() << "Error: Unable to open database" << db.lastError().text();
        return false;
    }

    return true;
}

void DatabaseManager::closeDatabase()
{
    if (db.isOpen()) {
        db.close();
    }
}

bool DatabaseManager::createUsersTable()
{
    if (!db.isOpen()) {
        qDebug() << "Error: Database is not open";
        return false;
    }

    QSqlQuery query;
    QString createTableQuery = "CREATE TABLE IF NOT EXISTS users ("
                               "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                               "lastname TEXT NOT NULL, "
                               "firstname TEXT NOT NULL, "
                               "middlename TEXT NOT NULL, "
                               "role INTEGER NOT NULL, "
                               "login TEXT NOT NULL UNIQUE, "
                               "password TEXT NOT NULL, "
                               "academic_degree TEXT DEFAULT NULL, "
                               "academic_title TEXT DEFAULT NULL, "
                               "position TEXT DEFAULT NULL)";

    if (!query.exec(createTableQuery)) {
        qDebug() << "Error: Failed to create table" << query.lastError().text();
        return false;
    }

    return true;
}

bool DatabaseManager::insertInitialData()
{
    if (!db.isOpen()) {
        qDebug() << "Error: Database is not open";
        return false;
    }

    struct User {
        QString lastname;
        QString firstname;
        QString middlename;
        int role;
        QString login;
        QString password;
        QString academic_degree;
        QString academic_title;
        QString position;
    };

    QList<User> users = {
        {"Иванов", "Иван", "Иванович", 0, "admin", "admin123", "", "", ""},
        {"Петров", "Петр", "Петрович", 1, "staff", "staff123", "", "", "Тьютор"},
        {"Сидорова", "Мария", "Сидорович", 2, "teacher", "teacher123", "Кандидат наук", "Профессор", ""},
        {"Смирнов", "Смир", "Смирнович", 3, "department", "dept123", " ", " ", " "}
    };

    QSqlQuery query;
    for (const User &user : users) {
        query.prepare("INSERT INTO users (lastname, firstname, middlename, role, login, password, "
                      "academic_degree, academic_title, position) "
                      "VALUES (:lastname, :firstname, :middlename, :role, :login, :password, "
                      ":academic_degree, :academic_title, :position)");
        query.bindValue(":lastname", user.lastname);
        query.bindValue(":firstname", user.firstname);
        query.bindValue(":middlename", user.middlename);
        query.bindValue(":role", user.role);
        query.bindValue(":login", user.login);
        query.bindValue(":password", user.password);
        query.bindValue(":academic_degree", user.academic_degree);
        query.bindValue(":academic_title", user.academic_title);
        query.bindValue(":position", user.position);

        if (!query.exec()) {
            qDebug() << "Error: Failed to insert initial data" << query.lastError().text();
            return false;
        }
    }

    return true;
}

QList<QString> DatabaseManager::getEmployeeNamesByRoles() const
{
    QList<QString> employeeNames;

    if (!db.isOpen()) {
        qDebug() << "Error: Database is not open";
        return employeeNames;
    }


    QSqlQuery query;
    query.prepare("SELECT lastname, firstname, middlename FROM users WHERE role = 1 or role = 2");
    if (!query.exec()) {
        qDebug() << "Error: Failed to query users" << query.lastError().text();
        return employeeNames;
    }

    while (query.next()) {
        QString fullName = query.value(0).toString() + " " +
                           query.value(1).toString() + " " +
                           query.value(2).toString();
        employeeNames.append(fullName);
    }

    qDebug() << "Employee names retrieved:" << employeeNames;
    return employeeNames;
}

int DatabaseManager::getUserIdFromFullName(const QString &fullName) const
{
    if (!db.isOpen()) {
        qDebug() << "Error: Database is not open";
        return -1; // Возвращаем -1 в случае ошибки
    }

    // Разбиваем полное имя на фамилию, имя и отчество
    QStringList nameParts = fullName.split(" ");

    if (nameParts.size() != 3) {
        qDebug() << "Error: Invalid full name format";
        return -1; // Возвращаем -1 в случае некорректного формата имени
    }

    // Извлекаем фамилию, имя и отчество
    QString lastname = nameParts[0];
    QString firstname = nameParts[1];
    QString middlename = nameParts[2];

    QSqlQuery query;
    query.prepare("SELECT id FROM users WHERE lastname = :lastname AND firstname = :firstname AND middlename = :middlename");
    query.bindValue(":lastname", lastname);
    query.bindValue(":firstname", firstname);
    query.bindValue(":middlename", middlename);

    if (!query.exec()) {
        qDebug() << "Error: Failed to query user id" << query.lastError().text();
        return -1; // Возвращаем -1 в случае ошибки
    }

    if (query.next()) {
        return query.value(0).toInt(); // Возвращаем user_id
    } else {
        qDebug() << "Error: User not found for full name" << fullName;
        return -1; // Возвращаем -1, если пользователь не найден
    }
}

int DatabaseManager::getUserIdFromLogin(const QString &login) const
{
    if (!db.isOpen()) {
        qDebug() << "Error: Database is not open";
        return -1; // Возвращаем -1 в случае ошибки
    }

    QSqlQuery query;
    query.prepare("SELECT id FROM users WHERE login = :login");
    query.bindValue(":login", login);

    if (!query.exec()) {
        qDebug() << "Error: Failed to query user id" << query.lastError().text();
        return -1; // Возвращаем -1 в случае ошибки
    }

    if (query.next()) {
        return query.value(0).toInt(); // Возвращаем user_id
    } else {
        qDebug() << "Error: User not found for login" << login;
        return -1; // Возвращаем -1, если пользователь не найден
    }
}
