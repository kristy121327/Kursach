#ifndef ADDTEACHER_H
#define ADDTEACHER_H

#include <QWidget>

namespace Ui {
class addteacher;
}

class addteacher : public QWidget
{
    Q_OBJECT

public:
    explicit addteacher(const QString &login, QWidget *parent = nullptr);
    ~addteacher();

private slots:
    void on_pushButton_clicked();

private:
    Ui::addteacher *ui;
    QString m_login; // Поле для хранения логина пользователя
};

#endif // ADDTEACHER_H
