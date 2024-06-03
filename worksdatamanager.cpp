#include "worksdatamanager.h"
#include "databasemanager.h"
#include <QDate>

WorksDataManager::WorksDataManager()
{
}

WorksDataManager::~WorksDataManager()
{
    closeDatabase();
}

bool WorksDataManager::openDatabase(const QString &path)
{
    m_db = QSqlDatabase::addDatabase("QSQLITE");
    m_db.setDatabaseName(path);

    if (!m_db.open()) {
        qDebug() << "Error: connection with database fail";
        return false;
    } else {
        qDebug() << "Database: connection ok";
        return true;
    }
}

void WorksDataManager::closeDatabase()
{
    if (m_db.isOpen()) {
        m_db.close();
    }
}

bool WorksDataManager::createTable()
{
    QSqlQuery query;
    QString createQuery = "CREATE TABLE IF NOT EXISTS additional_works ("
                          "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                          "name TEXT NOT NULL, "
                          "user_id INTEGER NOT NULL, "
                          "workload INTEGER NOT NULL, "
                          "start_date TEXT NOT NULL, "
                          "deadline TEXT NOT NULL, "
                          "payment REAL NOT NULL, "
                          "status INTEGER NOT NULL, "
                          "completion_date TEXT, "
                          "comment TEXT)";

    if (!query.exec(createQuery)) {
        qDebug() << "Couldn't create the table 'additional_works': one might already exist.";
        qDebug() << query.lastError();
        return false;
    }

    return true;
}

bool WorksDataManager::insertSampleData()
{
    if (!m_db.isOpen()) {
            qDebug() << "Error: Database is not open";
            return false;
        }

        QSqlQuery query;
        query.prepare("INSERT INTO additional_works (name, user_id, workload, start_date, deadline, payment, status, completion_date, comment) "
                      "VALUES (:name, :user_id, :workload, :start_date, :deadline, :payment, :status, :completion_date, :comment)");

        QList<QVariantList> sampleData = {
            {"Project A", 1, "Сложно", "2024-01-01", "2024-02-01", 1500.0, 0, "", ""},
            {"Project B", 2, "Средне", "2024-01-15", "2024-03-15", 1000.0, 3, "", "Измените титульный лист."},
            {"Project C", 3, "Легко", "2024-02-01", "2024-03-01", 2000.0, 1, "2024-02-28", ""}
        };

        for (const QVariantList &record : sampleData) {
               // Проверяем, существует ли уже запись с такими же значениями для ключевых полей
               QSqlQuery checkQuery;
               checkQuery.prepare("SELECT id FROM additional_works WHERE name = :name AND user_id = :user_id AND start_date = :start_date AND deadline = :deadline");
               checkQuery.bindValue(":name", record[0]);
               checkQuery.bindValue(":user_id", record[1]);
               checkQuery.bindValue(":start_date", record[3]);
               checkQuery.bindValue(":deadline", record[4]);
               if (!checkQuery.exec()) {
                   qDebug() << "Error: Failed to execute check query" << checkQuery.lastError().text();
                   return false;
               }

               // Если запись существует, пропускаем вставку данных
               if (checkQuery.next()) {
                   qDebug() << "Record already exists, skipping insertion";
                   continue;
               }

               // Если запись не существует, выполняем вставку данных
               query.bindValue(":name", record[0]);
               query.bindValue(":user_id", record[1]);
               query.bindValue(":workload", record[2]);
               query.bindValue(":start_date", record[3]);
               query.bindValue(":deadline", record[4]);
               query.bindValue(":payment", record[5]);
               query.bindValue(":status", record[6]);
               query.bindValue(":completion_date", record[7]);
               query.bindValue(":comment", record[8]);

               if (!query.exec()) {
                   qDebug() << "Error: Failed to insert data into additional_works" << query.lastError().text();
                   return false;
               }
           }
        return true;
}

// В классе WorksDataManager добавьте метод для получения списка названий работ
QList<QString> WorksDataManager::getAllWorkNames() const
{
    QList<QString> workNames;

    if (!m_db.isOpen()) {
        qDebug() << "Error: Database is not open";
        return workNames;
    }

    QSqlQuery query("SELECT name FROM additional_works WHERE status = 1");
    if (!query.exec()) {
        qDebug() << "Error: Failed to query additional_works" << query.lastError().text();
        return workNames;
    }

    while (query.next()) {
        workNames.append(query.value(0).toString());
    }

    return workNames;
}

bool WorksDataManager::updateProjectStatus(const QString &projectName, int status, const QString &comment, const QDate *completionDate)
{
    if (!m_db.isOpen()) {
        qDebug() << "Error: Database is not open";
        return false;
    }

    QSqlQuery query;
    query.prepare("UPDATE additional_works SET status = :status, completion_date = :completion_date, comment = :comment WHERE name = :name");
    query.bindValue(":status", status);

    // Преобразуем QDate в строку с использованием форматирования
    QString completionDateString = completionDate->toString("yyyy-MM-dd");
    query.bindValue(":completion_date", completionDateString);

    query.bindValue(":comment", comment);
    query.bindValue(":name", projectName);

    if (!query.exec()) {
        qDebug() << "Error: Failed to update project status";
        return false;
    }

    return true;
}

QList<QString> WorksDataManager::getUserWorkNames(const QString &login) const
{
    QList<QString> workNames;

    if (!db.openDatabase("mydatabase.db")) {
        qDebug() << "Ошибка: Не удалось открыть базу данных с пользователями";
        return workNames;
    }

    // Получаем идентификатор пользователя по логину
    int userId = db.getUserIdFromLogin(login);
    if (userId == -1) {
        qDebug() << "Error: Failed to get user id for login" << login;
        return workNames;
    }


    QSqlQuery query;
    query.prepare("SELECT name FROM additional_works WHERE user_id = :userId");
    query.bindValue(":userId", userId);

    if (!query.exec()) {
        qDebug() << "Ошибка: Не удалось выполнить запрос в additional_works" << query.lastError().text();
        return workNames;
    }

    while (query.next()) {
        workNames.append(query.value(0).toString());
    }

    return workNames;
}


bool WorksDataManager::updateProject(const QString &projectName, int status, const QDate *completionDate)
{
    if (!m_db.isOpen()) {
        qDebug() << "Error: Database is not open";
        return false;
    }

    QSqlQuery query;
    query.prepare("UPDATE additional_works SET status = :status, completion_date = :completion_date WHERE name = :name");
    query.bindValue(":status", status);

    // Преобразуем QDate в строку с использованием форматирования
    QString completionDateString = completionDate->toString("yyyy-MM-dd");
    query.bindValue(":completion_date", completionDateString);

    query.bindValue(":name", projectName);

    if (!query.exec()) {
        qDebug() << "Error: Failed to update project status";
        return false;
    }

    return true;
}
