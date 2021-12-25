#ifndef DATABASE_H
#define DATABASE_H

#include <QObject>
#include <QSql>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlDatabase>
#include <QFile>
#include <QDate>
#include <QDebug>

#define DATABASE_NAME           "data_base.sqlite"
#define TABLE                   "Task"
#define TABLE_ONE               "One"
#define TABLE_TWO               "Two"
#define TABLE_THREE             "Three"
#define TABLE_FOUR              "Four"
#define TABLE_FIVE              "Five"
#define TABLE_SIX               "Six"
#define SizeOfRow 6
#define SizeColumn 1024

class DbContext:public QObject
{
    Q_OBJECT
public:
     explicit DbContext(QObject *parent = 0);
    ~DbContext();

        void connectToDataBase();
        void insertIntoTable(const QList<QStringList> &data);
private:
        bool openDataBase();
        bool restoreDataBase();
        void closeDataBase();
        bool createTable();
private:

        QSqlDatabase    db;

};


#endif // DATABASE_H









