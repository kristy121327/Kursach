#ifndef ADDEMPLOYEE_H
#define ADDEMPLOYEE_H

#include <QWidget>

namespace Ui {
class addemployee;
}

class addemployee : public QWidget
{
    Q_OBJECT

public:
    explicit addemployee(const QString &login, QWidget *parent = nullptr);
    ~addemployee();

private slots:
    void on_pushButton_clicked();

private:
    Ui::addemployee *ui;
    QString m_login; // Поле для хранения логина пользователя
};

#endif // ADDEMPLOYEE_H
