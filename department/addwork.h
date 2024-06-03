#ifndef ADDWORK_H
#define ADDWORK_H

#include <QWidget>
#include <QSqlDatabase>
#include "databasemanager.h"

namespace Ui {
class AddWork;
}

class AddWork : public QWidget
{
    Q_OBJECT

public:
    explicit AddWork(QWidget *parent = nullptr);
    ~AddWork();

private slots:
    void on_backButton_clicked();

    void on_addButton_clicked();

private:
    Ui::AddWork *ui;
    //QSqlDatabase db;
    void openDatabase();
    DatabaseManager databasemanager;
};

#endif // ADDWORK_H
