#ifndef READYWORKS_H
#define READYWORKS_H

#include <QWidget>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QTableWidget>

namespace Ui {
class ReadyWorks;
}

class ReadyWorks : public QWidget
{
    Q_OBJECT

public:
    explicit ReadyWorks(QWidget *parent = nullptr);
    ~ReadyWorks();
    void loadData();
    void updateWorkRow(int status);

private slots:
    void on_backButton_clicked();

    void on_confirmButton_clicked();

private:
    Ui::ReadyWorks *ui;
    QSqlDatabase dbWorks;
    QSqlDatabase dbUsers;
    void openDatabases();
    void closeDatabases();
    int getSelectedWorkId();
};
#endif // READYWORKS_H
