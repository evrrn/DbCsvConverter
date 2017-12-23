#include "converter.h"


QString trimCSV(QString item)
{
    if((!item.isEmpty())&&(item[0] == QChar(34)))
        item.remove(0,1);
    if((!item.isEmpty())&&(!item.isNull())&(item[item.count()-1] == QChar(34)))
        item.remove(item.count()-1,1);
    if(!item.isEmpty())
        item = item.replace("\"\"","\"");
    return item;

}

bool ConverterModel::readFromCsvToModel()
{
    QFile csvfile(csvname);

    if (!QFile::exists(csvname))
    {
       output << "Файл " + csvname + " не существует.";
       return 1;
    }

    if (!csvfile.open(QIODevice::ReadOnly))
    {
        output << "Не удалось открыть файл " + csvname + " для записи";
        return 1;
    }

    clearTable();
    QChar _separator = ',';
    bool Quote = false;
    QStringList temp;
    QString item = "";
    int step = 0;

    QTextStream out(&csvfile);
    emit beginResetModel();
    while(!out.atEnd())
    {
        QString line(out.readLine().simplified());
        int count = line.count();
        for (int i = 0;i<count;i++)
        {
            if (line[i] == QChar(34))
            {
                if(Quote == false && item[0] == QChar(32))
                    item = "";
                Quote = (Quote) ? false : true;
            }

            if ((Quote != true)&(line[i] == _separator))
            {
                temp << trimCSV(item);
                item = "";
            }
            else
            {
                item += line[i];
            }

            if ((count-1 == i)&(Quote != true))
            {
                item = trimCSV(item);
                if (item != "")
                    temp << (item);

                if (step != 0)
                {
                    rows << temp;
                }
                else
                {
                    header = temp;
                }

                temp.clear();
                item = "";
            }
        }
        step++;
    }
    emit endResetModel();
    output << "Файл " + csvname + " успешно считан";

    csvfile.close();
    return 0;
}

QStringList ConverterModel::getColumnsType(){
    bool intFlag = true;
    bool doubleFlag = true;
    QStringList resultTypes;
    for(int i = 0; i < rows[0].size(); i++)
    {
        for(int j = 0; j < rows.size(); j++)
        {
            QString tempRec = rows[j][i];
            if(doubleFlag)
            {
                (tempRec.replace(",",".")).toDouble(&doubleFlag);
                if (tempRec.indexOf(".") != -1 && !intFlag)
                {
                    intFlag = !doubleFlag;
                }
            }
            if(intFlag)
            {
                tempRec.toInt(&intFlag);
            }
            if(!intFlag && !doubleFlag)
            {
                resultTypes.push_back("TEXT");
                break;
            }
        }

        if(intFlag)
        {
            resultTypes.push_back("INTEGER");
        }
        else
        {
            if(doubleFlag)
            {
                resultTypes.push_back("REAL");
            }
        }

        intFlag = true;
        doubleFlag = true;
    }
    return resultTypes;
}


bool ConverterModel::writeFromModelToDb()
{
    if (!QFile::exists(dbname))
    {
       output << "Не существует базы данных " + dbname;
       return 1;
    }
    QSqlDatabase::removeDatabase("db");
    QSqlDatabase sdb = QSqlDatabase::addDatabase("QSQLITE","db");
    sdb.setDatabaseName(dbname);

    if (!sdb.open())
    {
        output << "Ошибка: " + sdb.lastError().text();
        return 1;
    }

    QStringList columnsType = this->getColumnsType();

    QSqlDatabase::database().transaction();

    QSqlQuery *querydrop = new QSqlQuery("DROP TABLE " + tname, sdb);
    querydrop->exec();

    QString qtodb = "CREATE TABLE " + tname + " (";

    for(int i = 0; i < header.count(); i++)
    {
        qtodb += header[i] + " " + columnsType[i];//" TEXT";
        if(i != header.count() - 1)
        {
            qtodb += ", ";
        }
        else
            qtodb += ")";
    }

    QSqlQuery *query = new QSqlQuery(qtodb, sdb);
    query->exec();

    qtodb = "INSERT INTO " + tname + " (";
    for(int i = 0; i < header.count(); i++)
    {
        qtodb += header[i];
        if(i != header.count() - 1)
        {
            qtodb += ", ";
        }
        else
            qtodb += ") VALUES (";
    }

    for(int i = 0; i < rows.count(); i++)
    {
        QString tempString = qtodb;
        for(int j = 0; j < header.count(); j++)
        {
            tempString +="\'" + rows[i][j] + "\'";
            if(j != header.count() - 1)
            {
                tempString += ", ";
            }
            else
                tempString += ")";
        }

        query->prepare(tempString);
        bool f = query->exec();
        if(!f)
        {
            output << "Не удалось выполнить команду: " + tempString;
            QSqlDatabase::database().rollback();
            return 1;
        }
    }

    output << "Таблица " + tname + " в базе данных " + dbname + " успешно записана";
    QSqlDatabase::database().commit();
    sdb.close();
    return 0;
}
