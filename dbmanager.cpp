#include "dbmanager.h"

DbManager::DbManager(const QString &path)
{
    myDB = QSqlDatabase::addDatabase("QSQLITE");

    myDB.setDatabaseName(path);

    if(!myDB.open())
    {
        qDebug() << "Error: can't connect to database!" << endl;

    }
    else
    {
        qDebug() << "Database: Connected" << endl;
    }

    QSqlQuery query;
    query.prepare("PRAGMA foreign_keys = ON");

    if(query.exec())
    {
        qDebug() << "foreign keys on" << endl;
    }


}

void DbManager::InitCollegeList(const QString &path)//path to the excel file
{
   QSqlDatabase fileDB = QSqlDatabase::addDatabase("QODBC", "xlsx_connection");
   fileDB.setDatabaseName("DRIVER={Microsoft Excel Driver (*.xls, *.xlsx, *.xlsm, *.xlsb)};DBQ=" + path);
   if(fileDB.open())
   {
       qDebug() << "Excel connection successful" << endl;

       QSqlQuery *query = new QSqlQuery(fileDB);
       query->exec("select * from [" + QString("Distances") + "$A1:A111]");   //Distances is the sheet name!

       QSqlQuery * querytoDb = new QSqlQuery(myDB);

       querytoDb->exec("CREATE TABLE Colleges ("
                       "collegeName TEXT);");

       QString compare = "";

       while(query->next())
       {

           if(myDB.open())
           {

               querytoDb->prepare("INSERT INTO Colleges(collegeName) values(:collegeName)");

               QString column1 = query->value(0).toString();

               if(compare != column1)
               {
                   querytoDb->bindValue(":collegeName",query->value(0).toString());
                   qDebug() << querytoDb->exec();

               }
               compare = column1;
           }
       }

       fileDB.close();
   }
}

void DbManager::initSouvenirList(const QString &path)
{
    QSqlDatabase fileDB = QSqlDatabase::addDatabase("QODBC", "xlsx_connection");
    fileDB.setDatabaseName("DRIVER={Microsoft Excel Driver (*.xls, *.xlsx, *.xlsm, *.xlsb)};DBQ=" + path);

    if(fileDB.open())
    {
        qDebug() << "Excel connection successful" << endl;

        QSqlQuery *query = new QSqlQuery(fileDB);
        query->exec("select * from [" + QString("Souvenirs") + "$A1:C61]");

        QSqlQuery * querytoDb = new QSqlQuery(myDB);

        querytoDb->exec("CREATE TABLE Souvenirs ("
                        "collegeName TEXT,"
                        "souvenirName TEXT,"
                        "cost DOUBLE);");

        QString tempColumn1;
        QString check;

        while(query->next())
        {
            if(myDB.open())
            {
                querytoDb->prepare("INSERT INTO Souvenirs(collegeName, souvenirName, cost) VALUES(:collegeName, :souvenirName, :cost)");

                QString column1 = query->value(0).toString();
                check = column1;
                if(column1 == "" || column1 == " ")
                {
                    column1 = tempColumn1;
                }

                QString column2 = query->value(1).toString();

                double column3 = query->value(2).toDouble();

                if(check == "" && column2 != "")
                {
                    querytoDb->bindValue(":collegeName", column1);
                    querytoDb->bindValue(":souvenirName",column2);
                    querytoDb->bindValue(":cost",column3);
                    qDebug() << querytoDb->exec();

                }

                tempColumn1 = column1;
            }
        }
        fileDB.close();
    }
}

void DbManager::initDistanceList(const QString &path)
{
    QSqlDatabase fileDB = QSqlDatabase::addDatabase("QODBC", "xlsx_connection");
    fileDB.setDatabaseName("DRIVER={Microsoft Excel Driver (*.xls, *.xlsx, *.xlsm, *.xlsb)};DBQ=" + path);

    if(fileDB.open())
    {
        qDebug() << "Excel connection successful" << endl;

        QSqlQuery *query = new QSqlQuery(fileDB);
        query->exec("select * from [" + QString("Distances") + "$A1:C111]");

        QSqlQuery * querytoDb = new QSqlQuery(myDB);

        querytoDb->exec("CREATE TABLE Distances ("
                        "startCollege TEXT,"
                        "endCollege TEXT,"
                        "distance INTEGER);");

        while(query->next())
        {
            //QSqlDatabase myDB = QSqlDatabase::database("sqlite_connection");

            if(myDB.open())
            {
                querytoDb->prepare("INSERT INTO Distances(startCollege, endCollege, distance) VALUES(:startCollege, :endCollege, :distance)");

                QString column1 = query->value(0).toString();

                QString column2 = query->value(1).toString();

                int column3 = query->value(2).toInt();

                querytoDb->bindValue(":startCollege", column1);
                querytoDb->bindValue(":endCollege",column2);
                querytoDb->bindValue(":distance",column3);
                qDebug() << querytoDb->exec();
            }
        }
        fileDB.close();
    }
}

//QSqlDatabase::removeDatabase("xlsx_connection"); // need to put this out of scope of the initialised db

void DbManager::removeSou(const QString &souName, const QString &college)
{
    QSqlQuery *query = new QSqlQuery(myDB);

    if(souExists(souName, college))
    {
        if(myDB.open())
        {
            query->prepare("DELETE FROM Souvenirs WHERE (souvenirName) = (:souvenirName)");
            query->bindValue(":souvenirName", souName);

            if(query->exec())
            {
                qDebug() << "sou delete success!";
            }
            else
            {
                qDebug() << "sou delete failed!";
            }
        }
    }

}

int DbManager::cartQuantity(const QString college, const QString souvenir)
{
    int count = 0;
    QSqlQuery *query = new QSqlQuery(myDB);
    if(myDB.open())
    {
        query->prepare("SELECT quantity FROM Cart WHERE (college, souvenir) = (:college, :souvenir)");
        query->bindValue(":college", college);
        query->bindValue(":souvenir", souvenir);

        if(query->exec())
            qDebug() << "selected quantity";
        else
            qDebug() << "coudn't select quantity";

        while(query->next())
        {
            count = query->value(0).toInt();
            qDebug() << count;

            return count;
        }
    }

    return 0;
}

void DbManager::removeCart(const QString college, const QString souvenir)
{
    int count = cartQuantity(college, souvenir);
    count--;

    if(count != 0)
    {
        updateCart(college, souvenir, count);
    }
    else
    {
        QSqlQuery *query = new QSqlQuery(myDB);

        if(myDB.open())
        {
            query->prepare("DELETE FROM Cart WHERE (college, souvenir) = (:college, :souvenir)");
            query->bindValue(":college", college);
            query->bindValue(":souvenir", souvenir);

            if(query->exec())
                qDebug() << "cart delete success!";
            else
                qDebug() << "cart delete failed!";
        }
    }
}

void DbManager::addPurchase()
{
    QSqlQuery *query = new QSqlQuery(myDB);

    if(myDB.open())
    {
        query->prepare("INSERT INTO Purchases SELECT * FROM Cart");

        if(query->exec())
            qDebug() << "added to purchases!";
        else
            qDebug() << "coudn't add to purchases!";
    }
}

void DbManager::resetCart()
{
    QSqlQuery *query = new QSqlQuery(myDB);

    if(myDB.open())
    {
        query->prepare("DELETE FROM cart");

        if(query->exec())
            qDebug() << "Delete cART!";
        else
            qDebug() << "coudln't delete cart!";
    }
}

void DbManager::addCart(const QString trip, const QString college, const QString souvenir, const double price, const int count)
{
   QSqlQuery *query = new QSqlQuery(myDB);

   if(myDB.open())
   {
       query->prepare("INSERT INTO Cart(tripID, college, souvenir, price, quantity) VALUES(:tripID, :college, :souvenir, :price, :quantity)");
       query->bindValue(":tripID", trip);
       query->bindValue(":college", college);
       query->bindValue(":souvenir", souvenir);
       query->bindValue(":price", price);
       query->bindValue(":quantity",count);

       if(query->exec())
           qDebug() << "purchase add success!";
       else
           qDebug() << "pruchase add failed!";
   }

}


void DbManager::addSou(const QString &college, const QString &souName, const double &cost)
{
    QSqlQuery *query = new QSqlQuery(myDB);

    if(!souExists(souName, college))
    {
        if(myDB.open())
        {
            query->prepare("INSERT INTO Souvenirs(collegeName, souvenirName, cost) VALUES(:collegeName, :souvenirName, :cost)");
            query->bindValue(":collegeName", college);
            query->bindValue(":souvenirName", souName);
            query->bindValue(":cost", cost);

            if(query->exec())
                qDebug() << "sou add success!";
            else
                qDebug() << "sou add failed!";
        }
    }
    else
    {
        qDebug() << "name exists!";
    }
}

void DbManager::updateCart(const QString college, const QString souvenir, const int count)
{
    QSqlQuery *query = new QSqlQuery(myDB);

    if(myDB.open())
    {
        query->prepare("UPDATE Cart SET (quantity) = (:quantity) WHERE (college, souvenir) = (:college, :souvenir)");
        query->bindValue(":college", college);
        query->bindValue(":souvenir", souvenir);
        query->bindValue(":quantity", count);

        if(query->exec())
            qDebug() << "UPDATE cart";
        else
            qDebug() << "UPDATE failed: " << query->lastError() << endl;
    }

}

void DbManager::updateSou(const QString &souName, const QString &college, const double &spin, const QString &newSouvenir)
{
    QSqlQuery *query = new QSqlQuery(myDB);


    if(myDB.open())
    {
        query->prepare("UPDATE Souvenirs SET (souvenirName, cost) = (:newSouvenirName, :cost) "
                       "WHERE (collegeName, souvenirName) = (:collegeName, :souvenirName)");
        query->bindValue(":newSouvenirName", newSouvenir);
        query->bindValue(":collegeName", college);
        query->bindValue(":souvenirName", souName);
        query->bindValue(":cost", spin);

        if(query->exec())
        {
            qDebug() << "UPDATE WORKED" << endl;
        }
        else
        {
            qDebug() << "UPDATE failed: " << query->lastError() << endl;
        }
    }
}

void DbManager::addUser(const QString &user, const QString &pass)
{
    QSqlQuery *query = new QSqlQuery(myDB);
    QString userVal = "User";

   if(!userExists(user))
   {
    if(myDB.open())
    {
        query->exec("CREATE TABLE Logins ("
                    "Username TEXT,"
                    "Password TEXT,"
                    "UserValue TEXT);");

        query->prepare("INSERT INTO Logins(Username, Password, UserValue) VALUES(:Username, :Password, :UserValue)");

        query->bindValue(":Username", user);
        query->bindValue(":Password", pass);
        query->bindValue(":UserValue", userVal);
        qDebug() << query->exec();
    }
   }

}

bool DbManager::souExists(const QString &name, const QString &college)
{
    bool exists = false;

    QSqlQuery *checkQuery = new QSqlQuery(myDB);

    checkQuery->prepare("SELECT souvenirName FROM Souvenirs WHERE (collegeName, souvenirName) = (:collegeName, :souvenirName)");
    checkQuery->bindValue(":souvenirName", name);
    checkQuery->bindValue(":collegeName", college);


    if(checkQuery->exec())
    {
        if(checkQuery->next())
        {
            exists = true;
            QString souName = checkQuery->value("souvenirName").toString();
            QString college = checkQuery->value("collegeName").toString();
            qDebug() << souName << " " << college;
        }
    }
    else
    {
        qDebug() << "souvenir exists failed: " << checkQuery->lastError();
    }

    return exists;
}

bool DbManager::userExists(const QString &user)
{
    bool exists = false;

    QSqlQuery *checkQuery = new QSqlQuery(myDB);

    checkQuery->prepare("SELECT Username FROM Logins WHERE (Username) = (:Username)");
    checkQuery->bindValue(":Username", user);

    if(checkQuery->exec())
    {
        if(checkQuery->next())
        {
                exists = true;
                QString userName = checkQuery->value("Username").toString();
                qDebug() << userName;
        }
    }
    else
    {
        qDebug() << "person exists failed: " << checkQuery->lastError();
    }

    return exists;
}

void DbManager::clearDb()
{
    QSqlQuery *deleteQuery = new QSqlQuery(myDB);

    deleteQuery->prepare("DROP TABLE IF EXISTS Colleges");

    deleteQuery->exec();

    deleteQuery->prepare("DROP TABLE IF EXISTS Distances");

    deleteQuery->exec();

    deleteQuery->prepare("DROP TABLE IF EXISTS Souvenirs");

    deleteQuery->exec();

}

bool DbManager::isOpen() const
{
    return myDB.isOpen();
}

bool DbManager::checkAdmin(const QString &username) const
{
    bool admin = false;

    QSqlQuery *checkQuery = new QSqlQuery(myDB);

    checkQuery->prepare("SELECT UserValue FROM logins where (Username) = (:Username)");
    checkQuery->bindValue(":Username", username);

    if(checkQuery->exec())
    {
        if(checkQuery->next())
        {
            QString userVal = checkQuery->value("UserValue").toString();

            if(userVal == "admin")
            {
                admin = true;
            }
            qDebug() << admin;
        }
    }
    else
    {
        qDebug() << "Admin exists failed:";

    }

    if(admin)
    {
        qDebug() << "Admin";
    }

    return admin;
}

QString DbManager::getPassword(const QString &username) const
{
    QString password = "";
    QSqlQuery *getQuery = new QSqlQuery(myDB);
        getQuery->prepare("SELECT Password FROM logins WHERE (Username) = (:Username)");
        getQuery->bindValue(":Username", username);

        if (getQuery->exec())
        {
            if (getQuery->next())
            {
                password = getQuery->value("Password").toString();
                qDebug() << password;
            }
            else
            {
                qDebug() << "next query fail: " << getQuery->lastError();
            }
        }
        else
        {
            qDebug() << "person 1exists failed: " << getQuery->lastError();
        }

        return password;
}

void DbManager::addColleges(const QString &path)
{
    QSqlDatabase fileDB = QSqlDatabase::addDatabase("QODBC", "xlsx_connection");
    fileDB.setDatabaseName("DRIVER={Microsoft Excel Driver (*.xls, *.xlsx, *.xlsm, *.xlsb)};DBQ=" + path);

    if(fileDB.open())
    {
        qDebug() << "Excel connection successful"  ;

        QSqlQuery *query = new QSqlQuery(fileDB);
        query->exec("select * from [" + QString("New Campuses") + "$A2:C47]");

        QSqlQuery * querytoDb = new QSqlQuery(myDB);
        QSqlQuery * querytoList = new QSqlQuery(myDB);

        while(query->next())
        {
            if(myDB.open())
            {
                querytoDb->prepare("INSERT INTO Distances(startCollege, endCollege, distance) VALUES(:startCollege, :endCollege, :distance)");
                querytoList->prepare("INSERT OR REPLACE INTO Colleges(collegeName) values(:collegeName)");

                QString column1 = query->value(0).toString();
                QString column2 = query->value(1).toString();

                int column3 = query->value(2).toInt();

                querytoDb->bindValue(":startCollege", column1);
                querytoDb->bindValue(":endCollege",column2);
                querytoDb->bindValue(":distance",column3);
                qDebug() << querytoDb->exec();


                {
                    querytoList->bindValue(":collegeName",query->value(0).toString());
                    qDebug() << querytoList->exec();

                }

            }
        }

        fileDB.close();
    }
}

void DbManager::createTripTable()
{
    QSqlQuery *query = new QSqlQuery(myDB);
    QString userVal = "User";

    if(myDB.open())
    {
        query->exec("CREATE TABLE Trips ("
                    "tripID TEXT,"
                    "college TEXT,"
                    "tripProgress INT,"
                    "distanceToNext INT);");

        query->exec("CREATE TABLE Purchases ("
                    "tripID TEXT,"
                    "college TEXT,"
                    "souvenir TEXT,"
                    "price DOUBLE,"
                    "quantity INTEGER);");

    }

}

void DbManager::addTrip(QString tripID, QString plannedCollege, int index, int distanceTo)
{
    QSqlQuery *query = new QSqlQuery(myDB);

    if(myDB.open())
    {
        query->prepare("INSERT INTO Trips(tripID, college, tripProgress, distanceToNext) VALUES(:tripID, :college, :int, :distanceToNext)");

        query->bindValue(":tripID", tripID);
        query->bindValue(":college", plannedCollege);
        query->bindValue(":int", (index + 1));
        query->bindValue(":distanceToNext", distanceTo);
        qDebug() << query->exec();

    }

}


bool DbManager::tripIdExists(QString tripID)
{

    bool exists = false;

    QSqlQuery *checkQuery = new QSqlQuery(myDB);

    checkQuery->prepare("SELECT tripID FROM Trips WHERE (tripID) = (:tripID)");
    checkQuery->bindValue(":tripID", tripID);

    if(checkQuery->exec())
    {
        if(checkQuery->next())
        {
                exists = true;
        }
    }
    else
    {
        qDebug() << "trip id does not exist";
    }

    return exists;

}
