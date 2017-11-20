#include <QtSql>
#include <QSqlRecord>
#include <QFile>
#include "converter.h"

QByteArray getElementForCsv(QVariant elem) {
    return "\"" + elem.toByteArray() + "\"";
}

bool ConverterModel::readFromDbToModel()
{
    if (!QFile::exists(dbname))
    {
       output << "Не существует базы данных " + dbname;
       return 1;
    }

    QSqlDatabase sdb = QSqlDatabase::addDatabase("QSQLITE");
    sdb.setDatabaseName(dbname);

    if (!sdb.open()) {
        output << "Ошибка: " + sdb.lastError().text();
        return 1;
    }

    QSqlRecord columns = sdb.record(tname);

    if (columns.isEmpty()) {
        output << "Нет таблицы " + tname;
        return 1;
    }

    clearTable();
    int j;

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

    output << "База данных " + dbname + " успешно считана";
    return 0;
}

bool ConverterModel::writeFromModelToCsv()
{
    QFile csvfile(csvname);

    int i, j;
    int rows = rowCount(QModelIndex());
    int columns = columnCount(QModelIndex());

    if (QFile::exists(csvname))
        output << "Файл " + csvname + " будет перезаписан";
    else
        output << "Файл " + csvname + " будет создан";

    if (!csvfile.open(QIODevice::WriteOnly)) {
        output << "Не удалось открыть файл " + csvname + " для записи";
        return 1;
    }

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

    output << "Файл " + csvname + " успешно записан";
    return 0;
}


