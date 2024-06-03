#ifndef USERSDELETE_H
#define USERSDELETE_H

#include <QWidget>

namespace Ui {
class UsersDelete;
}

class UsersDelete : public QWidget
{
    Q_OBJECT

public:
    explicit UsersDelete(QWidget *parent = nullptr);
    ~UsersDelete();

private slots:
    void on_confirmButton_clicked();

    void on_backButton_clicked();

private:
    Ui::UsersDelete *ui;
};

#endif // USERSDELETE_H
