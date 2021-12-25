#include "Decorator.h"
#include <QCoreApplication>
#include <QList>
#include <QString>
#include <QStringList>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QFileInfo>


QString GetRandomString()
{
   const QString possibleCharacters("Zabcdefghijklmnopqrstuvwxyz0123456789");
   const int randomStringLength = 8; // assuming you want random strings of 8 characters

   QString randomString;
   for(int i=0; i<randomStringLength; ++i)
   {
       int index = qrand() % possibleCharacters.length();
       QChar nextChar = possibleCharacters.at(index);
       randomString.append(nextChar);
   }
   return randomString;
}

 QList<QStringList>  GetListString()
{
   QList<QStringList> test;
    for(int i=0;i<SizeColumn;++i){
        QList<QString> tmp;
      for(int j=0;j<SizeOfRow;++j){
      tmp.push_back(GetRandomString());
      }
       test.push_back(tmp);
    }


    return test;
}


void WriteToCSV(const QList<QStringList>& data,QString fileName)
{
    // Open csv-file
    QFile file(fileName);
    file.open(QIODevice::WriteOnly | QIODevice::Text);

    // Write data to file
    QTextStream stream(&file);
    QString separator(",");
    for (int i = 0; i < data.size(); ++i)
    {
        stream << data.at(i).join(separator) << "\n";
    }

    stream.flush();
    file.close();
}

QList<QStringList> ReadCSV(QString fileName)
{
    // Open csv-file
    QFile file(fileName);
    file.open(QIODevice::ReadOnly | QIODevice::Text);

    // Read data from file
    QTextStream stream(&file);
    QList<QStringList> data;
    QString separator(",");
    while (stream.atEnd() == false)
    {
        QString line = stream.readLine();
        data << line.split(separator);
    }

    file.close();
    return data;
}

void Print(const QList<QStringList>& data)
{
    for (int i = 0; i < data.size(); ++i)
    {
        qDebug() << data.at(i).join(", ");
    }
}
QList<QStringList> ReplaceNumbersAndDeleteStringLargeLetters(QList<QStringList> &data){
  int i=0;
  for (auto &subdata : data){

          i++;
          for (auto &elstring : subdata){

              elstring.replace(QRegExp("[13579]"), "#");
              if(elstring[0].isUpper()){
                    data.removeAt(i);
              }

          }

}

    return data;
}

int main(void)
{

    QList<QStringList> data=GetListString();
    WriteToCSV(data,"First_out.csv");
    QList<QStringList> dataReadCsv=ReadCSV("First_out.csv");
    QList<QStringList> newDataAfterFunck=ReplaceNumbersAndDeleteStringLargeLetters(dataReadCsv);
    WriteToCSV(newDataAfterFunck,"Second_out.csv");

    DbContext myDb;
    myDb.connectToDataBase();
    myDb.insertIntoTable(ReadCSV("First_out.csv"));


    return 0;
}
