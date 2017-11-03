#ifndef CONVERTER_H
#define CONVERTER_H

#include <QAbstractTableModel>
#include <QObject>
#include <QWidget>
#include <QList>

class ConverterModel : public QAbstractTableModel
{
    Q_OBJECT

private:
    QString namefrom, nameto, tname;
    QList<QList<QString>> rows;

public:
    ConverterModel(QObject *parent = 0);

    virtual int rowCount(const QModelIndex &parent) const override;
    virtual int columnCount(const QModelIndex &parent) const override;
    virtual QVariant data(const QModelIndex &index, int role) const override;

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
    bool readDbToModel(QString dbname, QString tname);

    //void convertDbToCsv(QString dbname, QString tname, QString csvname);
    //void convertCsvToDb(QString, QString, QString);
};

#endif // CONVERTER_H
