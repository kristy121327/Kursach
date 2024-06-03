#include "mainwindow.h"
#include <QApplication>

#include "databasemanager.h"
#include "worksdatamanager.h"
#include <QCoreApplication>
#include <QDebug>

DatabaseManager db; // База данных с пользователями
WorksDataManager m_db; // Менеджер работ

int main(int argc, char *argv[])
{
    setlocale(LC_ALL, "rus");
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    DatabaseManager dbManager;
    if (dbManager.openDatabase("mydatabase.db")) {
            if (dbManager.createUsersTable()) {
                qDebug() << "Users table created successfully";

                if (dbManager.insertInitialData()) {
                    qDebug() << "Initial data inserted successfully";
                } else {
                    qDebug() << "Failed to insert initial data";
                }
            } else {
                qDebug() << "Failed to create users table";
            }
        } else {
            qDebug() << "Failed to open database";
        }

    WorksDataManager dbWorks;
        if (dbWorks.openDatabase("mydatabase.db")) {
            if (dbWorks.createTable()) {
                qDebug() << "Works table created successfully";

                if (dbWorks.insertSampleData()) {
                    qDebug() << "Sample data inserted successfully";
                } else {
                    qDebug() << "Failed to insert sample data";
                }
            } else {
                qDebug() << "Failed to create works table";
            }
        } else {
            qDebug() << "Failed to open works database";
        }
    return a.exec();

}
