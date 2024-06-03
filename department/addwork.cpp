#include "addwork.h"
#include "ui_addwork.h"
#include "departmentaccount.h"
#include "databasemanager.h"
#include "listworks.h"

#include <QMessageBox>
#include <QStringListModel>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>


AddWork::AddWork(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AddWork)
{
    ui->setupUi(this);

       // Открываем базу данных
       if (!databasemanager.openDatabase("mydatabase.db")) {
           qDebug() << "Failed to open the database";
           // Обработка ошибки
           return;
       }

       // Получаем список сотрудников с ролями 1 и 2
       QList<QString> employeeNames = databasemanager.getEmployeeNamesByRoles();

       // Добавляем сотрудников в comboBox
       for (const QString &employeeName : employeeNames) {
           ui->employeeBox->addItem(employeeName);
       }


    // Закрываем базу данных
  //  databasemanager.closeDatabase();
}

AddWork::~AddWork()
{
    delete ui;
}


void AddWork::on_backButton_clicked()
{
    (new listWorks{})->show();
    this->close();
}


void AddWork::on_addButton_clicked()
{
    QSqlDatabase db = databasemanager.getDatabase(); // Получаем объект базы данных из DatabaseManager

    if (!db.isOpen()) {
        qDebug() << "Error: Database is not open";
        return;
    }

    QString username = ui->employeeBox->currentText().trimmed(); // Убедитесь, что удалили лишние пробелы
    qDebug() << "Selected username:" << username; // Проверяем, что выбрано правильное имя пользователя

    int userId = databasemanager.getUserIdFromFullName(username);
    qDebug() << "Retrieved user ID:" << userId; // Выводим в консоль ID пользователя, возвращаемый методом

    if (username.isEmpty()) {
        QMessageBox::critical(this, "Ошибка", "Не выбран пользователь.");
        qDebug() << "Error: Selected username is empty";
        return;
    }

    if (userId == -1) {
        QMessageBox::critical(this, "Ошибка", "Пользователь не найден.");
        qDebug() << "Error: User not found for username" << username;
        return;
    }

    QString name = ui->nameEdit->text();
    if (name.isEmpty()) {
        QMessageBox::critical(this, "Ошибка", "Название работы не может быть пустым.");
        qDebug() << "Error: Name of the work is empty";
        return;
    }

    int workloadIndex = ui->workloadBox->currentIndex(); // Получаем индекс выбранной сложности
    QString workload;
    switch (workloadIndex) {
        case 0:
            workload = "Сложно";
            break;
        case 1:
            workload = "Средне";
            break;
        case 2:
            workload = "Легко";
            break;
        default:
            QMessageBox::critical(this, "Ошибка", "Некорректная сложность работы.");
            qDebug() << "Error: Invalid workload";
            return;
    }

    // Используем QDateEdit для получения даты дедлайна
    QDate deadline = ui->deadlineEdit->date();
    QDate currentDate = QDate::currentDate();
    qDebug() << "Parsed deadline date:" << deadline << ", Current date:" << currentDate;

    if (deadline < currentDate) {
        QMessageBox::critical(this, "Ошибка", "Некорректная дата дедлайна. Дата не может быть раньше сегодняшнего дня.");
        qDebug() << "Error: Invalid deadline date or it's earlier than today";
        return;
    }

    QString startDate = currentDate.toString("yyyy-MM-dd");
    QString deadlineStr = deadline.toString("yyyy-MM-dd");
    double payment = ui->paymentBox->value();
    int status = 0;
    QString comment = ui->commentEdit->toPlainText();

    QSqlQuery query(db);
    query.prepare("INSERT INTO additional_works (name, user_id, workload, start_date, deadline, payment, status, completion_date, comment) "
                  "VALUES (:name, :user_id, :workload, :start_date, :deadline, :payment, :status, '', :comment)");
    query.bindValue(":name", name);
    query.bindValue(":user_id", userId);
    query.bindValue(":workload", workload);
    query.bindValue(":start_date", startDate);
    query.bindValue(":deadline", deadlineStr);
    query.bindValue(":payment", payment);
    query.bindValue(":status", status);
    query.bindValue(":comment", comment);

    if (!query.exec()) {
        QMessageBox::critical(this, "Ошибка", "Не удалось добавить данные в базу данных. " + query.lastError().text());
        qDebug() << "Error: Failed to insert data into additional_works" << query.lastError().text();
    } else {
        QMessageBox::information(this, "Успешно", "Данные успешно добавлены в базу данных.");
        qDebug() << "Data successfully inserted into additional_works";
    }
}
