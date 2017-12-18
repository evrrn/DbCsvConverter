#ifndef CONVERTER_H
#define CONVERTER_H

#include <QAbstractTableModel>
#include <QList>
#include <QtSql>
#include <QSqlRecord>
#include <QFile>

class ConverterModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    QString dbname, csvname, tname;
    QList<QStringList> rows;
    QStringList header;
    QStringList output;

public:
    /**
     * @brief Конструктор по умолчанию
     * @param parent
     */
    ConverterModel(QObject *parent = 0);
    /**
     * @brief Возвращает количество записей в таблице
     * @param parent - Виджет родитель
     * @return Количество записей
     */
    virtual int rowCount(const QModelIndex &parent) const override;
    /**
     * @brief Возвращает количество столбцов в таблице
     * @param parent - Виджет родитель
     * @return Количество столбцов
     */
    virtual int columnCount(const QModelIndex &parent) const override;
    /**
     * @brief data
     * @param index
     * @param role
     * @return
     */
    virtual QVariant data(const QModelIndex &index, int role) const override;
    /**
     * @brief Очистка таблицы
     */
    void clearTable();
    /**
     * @brief Чтение списка таблиц из базы данных
     * @return Список таблиц в контейнере QStringList
     */
    QStringList readListOfTables();
    /**
     * @brief Получение типов столбцов
     * Получение типов столбцов по считаным из CSV-файла данным для построения таблицы в базе данных.
     * @return Список типов в контейнере QStringList
     */
    QStringList getColumnsType();
    const bool operator==(const ConverterModel *model1);
public slots:
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
    /**
     * @brief Чтение таблицы из базы данных в модель
     * @return
     */
    bool readFromDbToModel();
    /**
     * @brief Запись данных из модели в CSV-файл
     * @return
     */
    bool writeFromModelToCsv();

    /**
     * @brief Чтение данных из CSV-файла в модель
     * @return
     */
    bool readFromCsvToModel();
    /**
     * @brief Запись таблицы из модели в базу данных
     * @return
     */
    bool writeFromModelToDb();

    // QAbstractItemModel interface
public:
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
};

#endif // CONVERTER_H
