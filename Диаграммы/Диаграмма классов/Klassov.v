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

class addemployee
{
  QString m_login
  void on_pushButton_clicked()
}

class addteacher
{
 void on_pushButton_clicked()
 QString m_login
}

class admaccount
{
  void on_exit_batton_clicked()
  void on_pushButton_clicked()
}


class AdminAdd
{
  void on_backButton_clicked()
  void on_confirmButton_clicked()
}

class users
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

class confirm
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

class listWorks
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

class confirmwork
{
  void on_backButton_clicked()
  void on_confirmButton_clicked()
  QString m_login
}

class empaccount
{
  void on_exit_clicked()
  void on_newworkButton_clicked()
  void on_accountButton_clicked()
  QString m_login
}

class empprofil1
{
  void setData()
  void on_backButton_clicked()
  QString m_login;
}

class empprofil2
{
  void on_backButton_clicked()
  QString m_login
}

class newworks
{
  void populateWorksTableForUser()
  void on_backButton_clicked()
  void on_confirmButton_clicked()
  QString m_login
}

listWorks --> MainWindow

MainWindow --> admaccount
MainWindow --> DepartmentAccount
MainWindow --> empaccount


admaccount --> users

users --> AdminAdd
users --> UsersDelete

AdminAdd --> addemployee
AdminAdd --> addteacher  


DepartmentAccount --> listWorks
DepartmentAccount --> ReadyWorks

ReadyWorks --> confirm

listWorks --> AddWork


empaccount --> empprofil1
empaccount --> empprofil2
empaccount --> newworks

newworks --> confirmwork

WorksDataManager --> DatabaseManager

addemployee --> DatabaseManager
addteacher --> DatabaseManager
AdminAdd --> DatabaseManager
users --> DatabaseManager
UsersDelete --> DatabaseManager

AddWork --> DatabaseManager
confirm --> WorksDataManager
listWorks --> WorksDataManager
listWorks --> DatabaseManager
ReadyWorks --> WorksDataManager
ReadyWorks --> DatabaseManager

confirmwork --> WorksDataManager
empaccount --> DatabaseManager
newworks --> WorksDataManager
newworks --> DatabaseManager



@enduml