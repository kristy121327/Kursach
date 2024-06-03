#ifndef EMPPROFIL1_H
#define EMPPROFIL1_H

#include <QWidget>

namespace Ui {
class empprofil1;
}

class empprofil1 : public QWidget
{
    Q_OBJECT

public:
    explicit empprofil1(const QString &login, QWidget *parent = nullptr);
    empprofil1(const empprofil1&) = default;
    ~empprofil1();
     void setData(const QString &lastname, const QString &firstname, const QString &middlename, const QString &position);

private slots:
     void on_backButton_clicked();

private:
    Ui::empprofil1 *ui;
    QString m_login; // Добавляем приватное поле для хранения логина пользователя

};

#endif // EMPPROFIL1_H
