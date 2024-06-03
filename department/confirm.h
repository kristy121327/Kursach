#ifndef CONFIRM_H
#define CONFIRM_H

#include <QWidget>
#include <QSqlDatabase>
#include "QStringListModel"
#include "readyworks.h"
#include "worksdatamanager.h"

namespace Ui {
class confirm;
}

class confirm : public QWidget
{
    Q_OBJECT

public:
    explicit confirm(QWidget *parent = nullptr);
    ~confirm();

private slots:
    void on_backButton_clicked();

    void on_rejectButton_clicked();

    void on_confirmButton_clicked();

private:
    Ui::confirm *ui;
    QSqlDatabase dbWorks;
    QStringListModel *model;
    WorksDataManager worksDataManager; // Объявление как член класса
    void openDatabase();
    void loadWorkNames();
};

#endif // CONFIRM_H
