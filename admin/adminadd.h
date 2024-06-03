#ifndef ADMINADD_H
#define ADMINADD_H

#include <QWidget>

namespace Ui {
class AdminAdd;
}

class AdminAdd : public QWidget
{
    Q_OBJECT

public:
    explicit AdminAdd(QWidget *parent = nullptr);
    ~AdminAdd();

private slots:
    void on_backButton_clicked();

    void on_confirmButton_clicked();

private:
    Ui::AdminAdd *ui;

};

#endif // ADMINADD_H
