#ifndef EMPACCOUNT_H
#define EMPACCOUNT_H

#include <QWidget>

namespace Ui {
class empaccount;
}

class empaccount : public QWidget
{
    Q_OBJECT

public:
    explicit empaccount(const QString &login, QWidget *parent = nullptr);
    ~empaccount();

private slots:
    void on_exit_clicked();

    void on_newworkButton_clicked();

    void on_accountButton_clicked();

private:
    Ui::empaccount *ui;
    QString m_login; // Добавим приватное поле для хранения логина
};

#endif // EMPACCOUNT_H
