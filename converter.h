#ifndef CONVERTER_H
#define CONVERTER_H

#include <QAbstractTableModel>
#include <QList>

class ConverterModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    QString dbname, csvname, tname;
    QList<QStringList> rows;
    QStringList header;
    QStringList output;

public:
    ConverterModel(QObject *parent = 0);

    virtual int rowCount(const QModelIndex &parent) const override;
    virtual int columnCount(const QModelIndex &parent) const override;
    virtual QVariant data(const QModelIndex &index, int role) const override;
    void clearTable();

private slots:

    void setDbName(QString name)
    {
        dbname = name;
    }

    void setCsvName(QString name)
    {
        csvname = name;
    }

    void setTableName(QString name)
    {
        tname = name;
    }

    void clearNames()
    {
        dbname = "";
        csvname = "";
        tname = "";
    }

public slots:
    bool readFromDbToModel();
    bool writeFromModelToCsv();

    // QAbstractItemModel interface
public:
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;

};

#endif // CONVERTER_H
