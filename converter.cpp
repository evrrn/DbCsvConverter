#include <QtSql>
#include <QSqlRecord>
#include <QFile>
#include "converter.h"

QByteArray getElementForCsv(QVariant elem) {
    return "\"" + elem.toByteArray() + "\"";
}

ConverterModel::ConverterModel(QObject *parent): QAbstractTableModel(parent)
{

}

int ConverterModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    return rows.count();
}

int ConverterModel::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    if (rows.count() == 0)
            return 0;

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

QVariant ConverterModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole){
        if (orientation == Qt::Horizontal) {
            if (section < header.size()) return header[section];
            else return "";
        }
    }
    return QAbstractTableModel::headerData(section, orientation, role);
}

bool ConverterModel::readFromDbToModel()
{
    QString dbname = "testDB";
    QString tname = "T3";

    QSqlDatabase sdb = QSqlDatabase::addDatabase("QSQLITE");
    sdb.setDatabaseName("../DbCsvConverter/db/" + dbname);

    if (!sdb.open())
          qDebug() << sdb.lastError().text();

    //  проверить, что таблица существует, а не создается

    int j;

    QSqlRecord columns = sdb.record(tname);

    emit beginRemoveColumns(QModelIndex(), 0, header.count()-1);
    header.clear();
    emit endRemoveColumns();

    emit beginInsertColumns(QModelIndex(), 0, columns.count()-1);
    for(j = 0; j < columns.count(); j++)
        header << columns.fieldName(j);
    emit endInsertColumns();

    QSqlQuery rowsize("SELECT count(*) FROM " + tname);
    rowsize.first();
    int rowcount = rowsize.value(0).toInt();

    QSqlQuery query("SELECT * FROM " + tname);
    emit beginInsertRows(QModelIndex(), 0, rowcount-1);
    while (query.next()) {
        rows << QStringList();
        for(j = 0; j < columns.count(); j++)
             rows.last() << query.value(j).toString();
    }
    emit endInsertRows();

    return 0;
}

bool ConverterModel::writeFromModelToCsv()
{
    QString csvname = "outcsv";
    QFile csvfile(csvname + ".csv");

    int i, j;
    int rows = rowCount(QModelIndex());
    int columns = columnCount(QModelIndex());

    if (csvfile.open(QIODevice::WriteOnly)) {

        for(j = 0; j < columns; j++) {
            csvfile.write(getElementForCsv(headerData(j, Qt::Horizontal, Qt::DisplayRole)));
            if (j + 1 != columns)
                csvfile.write(", ");
        }
        csvfile.write("\n");

        for(i = 0; i < rows; i++) {
            for(j = 0; j < columns; j++) {
                csvfile.write(getElementForCsv(data(index(i, j, QModelIndex()), Qt::DisplayRole)));
                if (j + 1 != columns)
                    csvfile.write(", ");
            }
            csvfile.write("\n");
        }
        csvfile.close();

    }    /*else
        qDebug() << csvfile.error().errorString();*/
    return 0;
}


