#include "confirmwork.h"
#include "ui_confirmwork.h"
#include "newworks.h"
#include "worksdatamanager.h"
#include <QDate>
#include <QStringListModel>

confirmwork::confirmwork(const QString &login, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::confirmwork),
    m_login(login) // Инициализируем приватное поле логина
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
    QList<QString> workNames = worksDataManager.getUserWorkNames(m_login);

    // Добавляем наименования работ в comboBox
    for (const QString& workName : workNames) {
        ui->workBox->addItem(workName);
    }
}

confirmwork::~confirmwork()
{
    delete ui;
}

void confirmwork::on_backButton_clicked()
{
    newworks *newWorksWindow = new newworks(m_login); // Передаем логин текущего пользователя, если он есть
    newWorksWindow->show();
    this->close();
}


void confirmwork::on_confirmButton_clicked()
{
    // Получаем выбранный проект из comboBox
    QString selectedWork = ui->workBox->currentText();

    // Обновляем статус проекта на "На проверке" и записываем текущую дату в базу данных
    WorksDataManager worksDataManager;
    if (!worksDataManager.openDatabase("mydatabase.db")) {
        qDebug() << "Failed to open the database";
        // Обработка ошибки
        return;
    }

    // Получаем текущую дату
    QDate currentDate = QDate::currentDate();

    if (!worksDataManager.updateProject(selectedWork, 1, &currentDate)) {
        qDebug() << "Failed to update project status";
        // Обработка ошибки
        return;
    }
    // Открываем окно newworks
        newworks *newWorksWindow = new newworks(m_login);
        newWorksWindow->show();
        this->close(); // Закрываем текущее окно confirmwork
}

