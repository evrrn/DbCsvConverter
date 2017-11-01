#ifndef DBTOCSV_H
#define DBTOCSV_H

void convertDbToCsv(QString dbname, QString tname, QString csvname);
QByteArray getElementForCsv(QString elem);

#endif // DBTOCSV_H

