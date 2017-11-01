#ifndef CONVERTER_H
#define CONVERTER_H

#include <QObject>
#include <QWidget>

class Converter : public QObject
{
    Q_OBJECT

private:
    QString namefrom, nameto, tname;

public:
    Converter()
    {
        namefrom = "";
        nameto = "";
        tname = "";
    }

    ~Converter()
    {
        delete &namefrom;
        delete &nameto;
        delete &tname;
    }

    void setNameFrom(QString name)
    {
        namefrom = name;
    }

    void setNameTo(QString name)
    {
        nameto = name;
    }

    void setTableName(QString name)
    {
        tname = name;
    }

signals:

private slots:
    void convertDbToCsv(QString dbname, QString tname, QString csvname);
    //void convertCsvToDb(QString, QString, QString);
};

#endif // CONVERTER_H
