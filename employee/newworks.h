#ifndef NEWWORKS_H
#define NEWWORKS_H

#include <QWidget>

namespace Ui {
class newworks;
}

class newworks : public QWidget
{
    Q_OBJECT

public:
    explicit newworks(const QString &login, QWidget *parent = nullptr);
    ~newworks();

    void populateWorksTableForUser(); // Объявление метода

private slots:
    void on_backButton_clicked();

    void on_confirmButton_clicked();

private:
    Ui::newworks *ui;
    QString m_login;
};

#endif // NEWWORKS_H
