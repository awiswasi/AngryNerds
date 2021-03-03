#include "DBManager.h"

DBManager::DBManager(QWidget *parent)
    : QWidget{parent}, QSqlDatabase(QSqlDatabase::addDatabase("QSQLITE"))
{
    setDatabaseName(QDir::currentPath() + "/initCampuses.db");

    if (!open())
    {
        qDebug() << "Connection to database failed";
    }
    else
    {
        qDebug() << "Connection to database succeeded";
    }
}

DBManager::~DBManager()
{
    if (open())
    {
        qDebug() << "Connection to database has been closed";
        QSqlDatabase::close();
    }
}

//DBManager *DBManager::instance()
//{
    // creates one and only one instance of the database
  //  static DBManager instance;
  //  return &instance;
//}

bool DBManager::verifyName(const QString &campusName)
{
    query.prepare("SELECT * FROM initCampuses WHERE endingColleges = :campusName");
    query.bindValue(":campusName", campusName);
    if (query.exec())
        return true;
    return false;
}

/*
int DBManager::GetDistances(const QString &college1, const QString &college2)
{

}
*/
