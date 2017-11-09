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
    QStringList header;
public:
    ConverterModel(QObject *parent = 0);

    virtual int rowCount(const QModelIndex &parent) const override;
    virtual int columnCount(const QModelIndex &parent) const override;
    virtual QVariant data(const QModelIndex &index, int role) const override;

    void setNameFrom(QString name="testDB")
    {
        namefrom = name;
    }

    void setNameTo(QString name="outT2")
    {
        nameto = name;
    }

    void setTableName(QString name="T2")
    {
        tname = name;
    }

signals:

private slots:
    bool readFromDbToModel(/*QString dbname, QString tname*/);
    bool writeFromModelToCsv(QString csvname);

    //void convertDbToCsv(QString dbname, QString tname, QString csvname);
    //void convertCsvToDb(QString, QString, QString);

    // QAbstractItemModel interface
public:
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;

};

#endif // CONVERTER_H
