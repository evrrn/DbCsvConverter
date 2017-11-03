#include <QtSql>
#include <QSqlRecord>
#include <QFile>
#include "converter.h"

QByteArray getElementForCsv(QString elem) {
    return "\"" + elem.toUtf8() + "\"";
}

ConverterModel::ConverterModel(QObject *parent): QAbstractTableModel(parent)
{

}

bool ConverterModel::readDbToModel(QString dbname, QString tname)
{
    QSqlDatabase sdb = QSqlDatabase::addDatabase("QSQLITE");
    sdb.setDatabaseName("../DbCsvConverter/db/" + dbname);

    if (!sdb.open())
          qDebug() << sdb.lastError().text();

    //QTextStream Qcout(stdout);

    //  проверить, что таблица существует, а не создается

    int i, j;

    QSqlRecord columns = sdb.record(tname);
    insertRows(0, 1);

    for(j = 0; j < columns.count(); j++)
        setData(index(0, j), columns.fieldName(j));

    QSqlQuery query("SELECT * FROM " + tname);

    insertRows(1, query.size());

    i = 1;
    while (query.next()) {
            for(j = 0; j < columns.count(); j++)
                setData(index(i++, j), query.value(j).toString());
    }

    return 0;

}


/*void ConverterModel::convertDbToCsv(QString dbname, QString tname, QString csvname) {

    QSqlDatabase sdb = QSqlDatabase::addDatabase("QSQLITE");
    sdb.setDatabaseName("../DbCsvConverter/db/" + dbname);

    if (!sdb.open())
          qDebug() << sdb.lastError().text();

    QTextStream Qcout(stdout);

    //  проверить, что таблица существует, а не создается

    QFile csvfile(csvname + ".csv");
    QString str;
    int i;

    QSqlRecord columns = sdb.record(tname);

    if (csvfile.open(QIODevice::WriteOnly)) {

        for(i = 0; i < columns.count(); i++) {
            csvfile.write(getElementForCsv(columns.fieldName(i)));
            if (i + 1 != columns.count())
                csvfile.write(", ");
        }
        csvfile.write("\n");

        QSqlQuery query("SELECT * FROM " + tname);

        while (query.next()) {
            for(i = 0; i < columns.count(); i++) {
                str = query.value(i).toString();
                csvfile.write(getElementForCsv(str));
                if (i + 1 != columns.count())
                    csvfile.write(", ");
            }
            csvfile.write("\n");
        }

        csvfile.close();

        }    /*else
        qDebug() << csvfile.error().errorString();

}*/

int ConverterModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid()) return 0;
    return rows.count();

}

int ConverterModel::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid()) return 0;
    return rows.first().count();

}

QVariant ConverterModel::data(const QModelIndex &index, int role) const
{
    if (role == Qt::DisplayRole){
        if (!index.isValid())
            return QVariant();
        return rows.at(index.row()).at(index.column());
    }
    return QVariant();
}


