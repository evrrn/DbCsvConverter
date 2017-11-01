#ifndef CONVERTER_H
#define CONVERTER_H

#include <QObject>
#include <QWidget>
//#include <QDir>

class Converter : public QObject
{
    Q_OBJECT

private:
    QString filefrom, fileto, tname;

public:
    explicit Converter(QObject *parent = 0);

    Converter();
    ~Converter() {
        delete &filefrom;
        delete &fileto;
        delete &tname;
    }


signals:

private slots:
    //void convertDbToCsv(QString, QString, QString);
    //void convertCsvToDb(QString, QString, QString);
};

#endif // CONVERTER_H
