#ifndef USERS_H
#define USERS_H

#include <QWidget>

namespace Ui {
class users;
}

class users : public QWidget
{
    Q_OBJECT

public:
    explicit users(QWidget *parent = nullptr);
    ~users();

private slots:
    void on_backButton_clicked();

    void on_addButton_clicked();

    void on_deleteButton_clicked();

private:
    Ui::users *ui;
    void loadData();
};

#endif // USERS_H
