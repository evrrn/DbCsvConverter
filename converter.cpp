#include <QtSql>
#include <QFile>
#include "converter.h"

QByteArray getElementForCsv(QString elem) {
    return "\"" + elem.toUtf8() + "\"";
}

void Converter::convertDbToCsv(QString dbname, QString tname, QString csvname) {

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
        qDebug() << csvfile.error().errorString();*/

}
