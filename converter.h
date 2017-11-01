#ifndef CONVERTER_H
#define CONVERTER_H

#include <QObject>
#include <QWidget>

class Converter : public QObject
{
    Q_OBJECT

private:
    QString filefrom, fileto, tname;

public:
    Converter()
    {
        filefrom = "";
        fileto = "";
        tname = "";
    }

    ~Converter()
    {
        delete &filefrom;
        delete &fileto;
        delete &tname;
    }

signals:

private slots:
    void convertDbToCsv(QString dbname, QString tname, QString csvname);
    //void convertCsvToDb(QString, QString, QString);
};

#endif // CONVERTER_H
