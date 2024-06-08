@startuml

hide empty methods
hide empty members

class MainWindow
{
 on_actionListWorks_triggered()
 on_vhodButton_clicked()
 on_enterPressed()
 listWorks *listWorksWindow
}
 
class DatabaseManager
{
 bool openDatabase()
 void closeDatabase()
 QSqlDatabase getDatabase()
 bool createUsersTable()
 bool insertInitialData()
 QList<QString> getEmployeeNamesByRoles()
 int getUserIdFromFullName()
 int getUserIdFromLogin()
 mutable QSqlDatabase db
}

class WorksDataManager
{
 bool openDatabase(const QString &path)
 void closeDatabase()
 bool createTable()
 bool insertSampleData()
 QList<QString> getAllWorkNames()
 QList<QVariantList> getWorksForUser()
 QList<QString> getUserWorkNames()
 bool updateProjectStatus()
 bool updateProject()
 QSqlDatabase m_db
 DatabaseManager db

}

class AddEmployee
{
  QString m_login
  void on_pushButton_clicked()
}

class AddTeacher
{
 void on_pushButton_clicked()
 QString m_login
}

class AdminMainWindow
{
  void on_exit_batton_clicked()
  void on_pushButton_clicked()
}


class AdminAdd
{
  void on_backButton_clicked()
  void on_confirmButton_clicked()
}

class AllUsers
{
  void on_backButton_clicked()
  void on_addButton_clicked()
  void on_deleteButton_clicked()
  void loadData()
}

class UsersDelete
{
  void on_confirmButton_clicked()
  void on_backButton_clicked()
}

class AddWork
{
  void on_backButton_clicked()
  void on_addButton_clicked()
  QSqlDatabase db
  void openDatabase()
  DatabaseManager databasemanager
}

class ConfirmThisWork
{
  void on_backButton_clicked()
  void on_rejectButton_clicked()
  void on_confirmButton_clicked()
  QSqlDatabase dbWorks
  QStringListModel *model
  WorksDataManager worksDataManager
  void openDatabase()
  void loadWorkNames()
}

class DepartmentAccount
{
  void on_exitButton_clicked()
  void on_NewWorksButton_clicked()
  void on_ConfirmWorksButton_2_clicked()
}

class ListWorks
{
  
  void on_backButton_clicked()
  void on_addButton_clicked()
  QSqlDatabase dbWorks
  QSqlDatabase dbUsers
  void openDatabases()
  void closeDatabases()
  void loadData()
}

class ReadyWorks
{
  void on_backButton_clicked()
  void on_confirmButton_clicked()
  void loadData()
  void updateWorkRow(int status)
  QSqlDatabase dbWorks
  QSqlDatabase dbUsers
  void openDatabases()
  void closeDatabases()
  int getSelectedWorkId()
}

class ConfirmWork
{
  void on_backButton_clicked()
  void on_confirmButton_clicked()
  QString m_login
}

class EmployeeMainWindow
{
  void on_exit_clicked()
  void on_newworkButton_clicked()
  void on_accountButton_clicked()
  QString m_login
}

class StaffProfil
{
  void setData()
  void on_backButton_clicked()
  QString m_login;
}

class TeacherProfil
{
  void on_backButton_clicked()
  QString m_login
}

class NewWorks
{
  void populateWorksTableForUser()
  void on_backButton_clicked()
  void on_confirmButton_clicked()
  QString m_login
}

ListWorks --> MainWindow

MainWindow --> AdminMainWindow
MainWindow --> DepartmentAccount
MainWindow --> EmployeeMainWindow


AdminMainWindow --> AllUsers

AllUsers --> AdminAdd
AllUsers --> UsersDelete

AdminAdd --> AddEmployee
AdminAdd --> AddTeacher  

DepartmentAccount --> ListWorks
DepartmentAccount --> ReadyWorks

ReadyWorks --> ConfirmThisWork

ListWorks --> AddWork


EmployeeMainWindow --> StaffProfil
EmployeeMainWindow --> TeacherProfil
EmployeeMainWindow --> NewWorks

NewWorks --> ConfirmWork

WorksDataManager --> DatabaseManager

AddEmployee --> DatabaseManager
AddTeacher --> DatabaseManager
AdminAdd --> DatabaseManager
AllUsers --> DatabaseManager
UsersDelete --> DatabaseManager

AddWork --> DatabaseManager
ConfirmThisWork --> WorksDataManager
ListWorks --> WorksDataManager
ListWorks --> DatabaseManager
ReadyWorks --> WorksDataManager
ReadyWorks --> DatabaseManager

ConfirmWork --> WorksDataManager
EmployeeMainWindow --> DatabaseManager
NewWorks --> WorksDataManager
NewWorks --> DatabaseManager



@enduml