#ifndef CONFIRMWORK_H
#define CONFIRMWORK_H

#include <QWidget>

namespace Ui {
class confirmwork;
}

class confirmwork : public QWidget
{
    Q_OBJECT

public:
    explicit confirmwork(const QString &login, QWidget *parent = nullptr);
    ~confirmwork();

private slots:
    void on_backButton_clicked();

    void on_confirmButton_clicked();

private:
    Ui::confirmwork *ui;
    QString m_login; // Добавляем приватное поле для хранения логина пользователя
};

#endif // CONFIRMWORK_H
