#ifndef DBMANAGER_H
#define DBMANAGER_H

#include <QWidget>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlQueryModel>
#include <QDir>
#include <QString>
#include <QDebug>



class DBManager : public QWidget, public QSqlDatabase
{
    Q_OBJECT;

public:
    explicit DBManager(QWidget *parent = nullptr);


    ~DBManager();

   // static DBManager *instance();


    DBManager(const DBManager &) = delete;


    DBManager &operator=(const DBManager &) = delete;

   bool verifyName (const QString &name);

    int GetDistances(const QString &city1, const QString &city2);

    QSqlQuery query; //!< used to query the database

private:

   // QSqlQuery query;


   // explicit DBManager(QWidget *parent = nullptr);


   // ~DBManager();
};

#endif // DBMANAGER_H


