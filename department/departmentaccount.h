#ifndef DEPARTMENTACCOUNT_H
#define DEPARTMENTACCOUNT_H

#include <QWidget>

namespace Ui {
class DepartmentAccount;
}

class DepartmentAccount : public QWidget
{
    Q_OBJECT

public:
    explicit DepartmentAccount(QWidget *parent = nullptr);
    ~DepartmentAccount();

private slots:
    void on_exitButton_clicked();

    void on_NewWorksButton_clicked();

    void on_ConfirmWorksButton_2_clicked();

private:
    Ui::DepartmentAccount *ui;
};

#endif // DEPARTMENTACCOUNT_H
