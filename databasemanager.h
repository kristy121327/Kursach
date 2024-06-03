#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QString>

class DatabaseManager : public QObject
{
    Q_OBJECT

public:
    explicit DatabaseManager(QObject *parent = nullptr);
    ~DatabaseManager();

    bool openDatabase(const QString &dbName) const;
    void closeDatabase();
    QSqlDatabase getDatabase() const {
            return db;
        }
    bool createUsersTable();
    bool insertInitialData();
    QList<QString> getEmployeeNamesByRoles() const;
    int getUserIdFromFullName(const QString &fullName) const; // Новый метод для получения user_id по имени пользователя
    int getUserIdFromLogin(const QString &login) const;
    // метод для получения всех пользователей в таблицу админа

private:
     mutable QSqlDatabase db;
};

#endif // DATABASEMANAGER_H
