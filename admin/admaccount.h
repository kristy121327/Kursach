#ifndef ADMACCOUNT_H
#define ADMACCOUNT_H

#include <QWidget>

namespace Ui {
class admaccount;
}

class admaccount : public QWidget
{
    Q_OBJECT

public:
    explicit admaccount(QWidget *parent = nullptr);
    ~admaccount();

private slots:
    void on_exit_batton_clicked();

    void on_pushButton_clicked();

private:
    Ui::admaccount *ui;
};

#endif // ADMACCOUNT_H
