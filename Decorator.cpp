#include "Decorator.h"


DbContext::DbContext(QObject *parent) : QObject(parent)
{

}

DbContext::~DbContext()
{

}


void DbContext::connectToDataBase()
{
    if(!QFile("./" DATABASE_NAME).exists()){
        this->restoreDataBase();
    } else {
        this->openDataBase();
    }
}


bool DbContext::restoreDataBase()
{

    if(this->openDataBase()){

        return (this->createTable()) ? true : false;
    } else {
        qDebug() << "Не удалось восстановить базу данных";
        return false;
    }
    return false;
}

bool DbContext::openDataBase()
{

    db = QSqlDatabase::addDatabase("QSQLITE");
    //db.setHostName(DATABASE_HOSTNAME);
    db.setDatabaseName("./" DATABASE_NAME);
    if(db.open()){
        return true;
    } else {
        return false;
    }
}

void DbContext::closeDataBase()
{
    db.close();
}



bool DbContext::createTable()
{

    QSqlQuery query;

    if(!query.exec( "CREATE TABLE " TABLE " ("
                            TABLE_ONE      " VARCHAR(255)    NOT NULL,"
                            TABLE_TWO      " VARCHAR(255)    NOT NULL,"
                            TABLE_THREE    " VARCHAR(255)    NOT NULL,"
                            TABLE_FOUR     " VARCHAR(255)    NOT NULL,"
                            TABLE_FIVE     " VARCHAR(255)    NOT NULL,"
                            TABLE_SIX      " VARCHAR(255)    NOT NULL"
                        " )"
                    )){
        qDebug() << "DataBase: error of create " << TABLE;
        return false;
    }else{
        return true;
    }
    return false;

}

void DbContext::insertIntoTable(const QList<QStringList> &data)
{

    QSqlQuery query;

    qDebug()<<"Inserting";
    int i=0;
    for (auto &subdata : data){
    query.prepare("INSERT INTO " TABLE " ( " TABLE_ONE ", "
                                             TABLE_TWO ", "
                                             TABLE_THREE ", "
                                             TABLE_FOUR ", "
                                             TABLE_FIVE ", "
                                             TABLE_SIX " ) "
                  "VALUES (:One, :Two, :Three, :Four, :Five, :Six )");
    query.bindValue(":One",        data.at(i).at(0));
    query.bindValue(":Two",        data.at(i).at(1));
    query.bindValue(":Three",      data.at(i).at(2));
    query.bindValue(":Four",       data.at(i).at(3));
    query.bindValue(":Five",       data.at(i).at(4));
    query.bindValue(":Six",        data.at(i).at(5));
    // После чего выполняется запросом методом exec()
    if(!query.exec()){
        qDebug() << "error insert into " << TABLE;
}
     i++;

}
}




