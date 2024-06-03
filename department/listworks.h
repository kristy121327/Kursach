#ifndef LISTWORKS_H
#define LISTWORKS_H

#include <QWidget>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QTableWidget>

namespace Ui {
class listWorks;
}

class listWorks : public QWidget
{
    Q_OBJECT

public:
    explicit listWorks(QWidget *parent = nullptr);
    ~listWorks();
    void loadData();

private slots:

    void on_backButton_clicked();

    void on_addButton_clicked();

private:
    Ui::listWorks *ui;
    QSqlDatabase dbWorks;
    QSqlDatabase dbUsers;
    void openDatabases();
    void closeDatabases();
};

#endif // LISTWORKS_H
