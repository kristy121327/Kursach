    #ifndef MAINWINDOW_H
    #define MAINWINDOW_H

    #include <QMainWindow>
    #include "databasemanager.h"
    #include "admin/admaccount.h"
    #include "department/departmentaccount.h"
    #include "employee/empaccount.h"
    #include "department/listworks.h" // Включаем заголовочный файл listworks.h



    QT_BEGIN_NAMESPACE
    namespace Ui { class MainWindow; }
    QT_END_NAMESPACE

    class MainWindow : public QMainWindow
    {
        Q_OBJECT

    public:
        MainWindow(QWidget *parent = nullptr);
        ~MainWindow();

    private slots:
        void on_actionListWorks_triggered();

        void on_vhodButton_clicked();

        void on_enterPressed();

    private:
        Ui::MainWindow *ui;
        listWorks *listWorksWindow;
    };
    #endif // MAINWINDOW_H
