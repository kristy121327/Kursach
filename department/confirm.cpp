#include "confirm.h"
#include "worksdatamanager.h"
#include "ui_confirm.h"
#include "listworks.h"
#include <QStringListModel>
#include <QDate>

confirm::confirm( QWidget *parent) :
    QWidget(parent, Qt::Window),
    ui(new Ui::confirm)

{
    ui->setupUi(this);

    // Создаем экземпляр класса WorksDataManager
    WorksDataManager worksDataManager;

    // Открываем базу данных
    if (!worksDataManager.openDatabase("mydatabase.db")) {
        qDebug() << "Failed to open the database";
        // Обработка ошибки
        return;
    }

    // Получаем список наименований работ из базы данных
    QList<QString> workNames = worksDataManager.getAllWorkNames();

    // Добавляем наименования работ в comboBox
    for (const QString& workName : workNames) {
        ui->worksBox->addItem(workName);
    }
}


confirm::~confirm()
{
    delete ui;
}


void confirm::on_backButton_clicked( )
{
    this->close();
}



void confirm::on_rejectButton_clicked()
{
    // Получаем выбранный проект из comboBox
    QString selectedWork = ui->worksBox->currentText();

    // Получаем комментарий из QTextEdit
    QString comment = ui->commentEdit->toPlainText();

    // Обновляем статус проекта на "Отклонено" в базе данных
    WorksDataManager worksDataManager;
    if (!worksDataManager.openDatabase("mydatabase.db")) {
        qDebug() << "Failed to open the database";
        // Обработка ошибки
        return;
    }

    if (!worksDataManager.updateProjectStatus(selectedWork, 3, comment)) {
        qDebug() << "Failed to update project status";
        // Обработка ошибки
        return;
    }
}


void confirm::on_confirmButton_clicked()
{
    // Получаем выбранный проект из comboBox
    QString selectedWork = ui->worksBox->currentText();

    // Получаем комментарий из QTextEdit
    QString comment = ui->commentEdit->toPlainText();

    // Обновляем статус проекта на "Принято" и записываем комментарий и текущую дату в базу данных
    WorksDataManager worksDataManager;
    if (!worksDataManager.openDatabase("mydatabase.db")) {
        qDebug() << "Failed to open the database";
        // Обработка ошибки
        return;
    }

    // Получаем текущую дату
    QDate currentDate = QDate::currentDate();

    if (!worksDataManager.updateProjectStatus(selectedWork, 2, comment, &currentDate)) {
        qDebug() << "Failed to update project status";
        // Обработка ошибки
        return;
    }

    (new listWorks{})->show();
    this->close();
}
