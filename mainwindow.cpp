#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QDebug>

#include "department/listworks.h"
#include "databasemanager.h"
#include "admin/admaccount.h"
#include "department/departmentaccount.h"
#include "employee/empaccount.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Подключение слотов для обработки нажатия клавиши Enter
    connect(ui->usernameLineEdit, &QLineEdit::returnPressed, this, &MainWindow::on_enterPressed);
    connect(ui->passwordLineEdit, &QLineEdit::returnPressed, this, &MainWindow::on_enterPressed);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_vhodButton_clicked()
{
    QString login = ui->usernameLineEdit->text();
    QString password = ui->passwordLineEdit->text();

    DatabaseManager dbManager;
    if (dbManager.openDatabase("mydatabase.db")) {
        QSqlQuery query;
        query.prepare("SELECT role FROM users WHERE login = :login AND password = :password");
        query.bindValue(":login", login);
        query.bindValue(":password", password);

        if (query.exec() && query.next()) {
            int role = query.value(0).toInt();
            if (role == 0) {
                admaccount *admAccount = new admaccount();
                admAccount->show();
                this->close();
            } else if (role == 3) {
                DepartmentAccount *departmentAccount = new DepartmentAccount();
                departmentAccount->show();
                this->close();
            } else {
                empaccount *empAccount = new empaccount(login);
                empAccount->show();
                this->close();
            }
        } else {
            // Если запрос к базе данных не вернул результат, выводим сообщение об ошибке
            QMessageBox::critical(this, "Ошибка", "Неверный логин или пароль");
            ui->usernameLineEdit->clear();
            ui->passwordLineEdit->clear();
        }
    } else {
        qDebug() << "Failed to open database";
    }
}

void MainWindow::on_actionListWorks_triggered()
{
    listWorksWindow = new listWorks(this);
    listWorksWindow->show();
}

void MainWindow::on_enterPressed()
{
    // Имитация нажатия кнопки "Войти"
    ui->vhodButton->click();
}
