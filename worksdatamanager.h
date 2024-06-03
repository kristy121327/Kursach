#ifndef WORKSDATAMANAGER_H
#define WORKSDATAMANAGER_H

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include "databasemanager.h"

class WorksDataManager
{
public:
    WorksDataManager();
    ~WorksDataManager();

    bool openDatabase(const QString &path);
    void closeDatabase();

    bool createTable();
    bool insertSampleData();

    QList<QString> getAllWorkNames() const;

    QList<QVariantList> getWorksForUser(const QString &username);

    QList<QString> getUserWorkNames(const QString &login) const;

    bool updateProjectStatus(const QString &projectName, int status, const QString &comment, const QDate *completionDate = nullptr);

    bool updateProject(const QString &projectName, int status, const QDate *completionDate);

private:
    QSqlDatabase m_db;
    DatabaseManager db; // Изменяем тип поля db

};

#endif // WORKSDATAMANAGER_H
