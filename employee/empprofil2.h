#ifndef EMPPROFIL2_H
#define EMPPROFIL2_H

#include <QWidget>

namespace Ui {
class empprofil2;
}

class empprofil2 : public QWidget
{
    Q_OBJECT

public:
     explicit empprofil2(const QString &login, QWidget *parent = nullptr);
     empprofil2(const empprofil2&) = default;
    ~empprofil2();
     void setData(const QString &lastname, const QString &firstname, const QString &middlename, const QString &academic_degree, const QString &academic_title);

private slots:
     void on_backButton_clicked();

private:
    Ui::empprofil2 *ui;
    QString m_login;
};

#endif // EMPPROFIL2_H
