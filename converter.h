/**
    *@file
    *@brief Заголовочный файл с описанием класса ConverterModel

    Данный файл содержит в себе описание полей и функций класса ConverterModel,
    который считывает, хранит и записывает данные, поступающие в виде таблицы либо CSV-файла

*/

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
    /// Строковые параметры, хранящие имя базы данных, CSV-файла и таблицы соответственно
    QString dbname, csvname, tname;

    /// Список списков строк, элементами которого являются ячейки входной таблицы или CSV-файла
    QList<QStringList> rows;

    /// Список строк, элементы которого представляют собой названия столбцов входной таблицы или CSV-файла
    QStringList header;

    /// Список строк, хранящий информационные сообщения за все время работы приложения
    QStringList output;

public:

    /**
     * @brief Конструктор по умолчанию
     * @param parent - Объект-родитель
     */
    ConverterModel(QObject *parent = 0);

    /**
     * @brief Возвращает количество записей в модели
     * @param parent - Индекс модели
     * @return Количество записей либо 0, если родитель не пуст
     */
    virtual int rowCount(const QModelIndex &parent) const override;

    /**
     * @brief Возвращает количество столбцов в модели
     * @param parent - Индекс модели
     * @return Количество столбцов либо 0, если родитель не пуст или записей нет
     */
    virtual int columnCount(const QModelIndex &parent) const override;

    /**
     * @brief Возвращает значение элемента модели
     * @param index - Индекс элемента
     * @param role - Роль элемента
     * @return Значение элемента с данным индексом, либо QVariant, если индекс невалиден или роль элемента отлична от Qt::DisplayRole
     */
    virtual QVariant data(const QModelIndex &index, int role) const override;

    /**
     * @brief Чтение списка таблиц из базы данных
     * @return Список таблиц в контейнере QStringList
     */
    QStringList readListOfTables();

    /**
     * @brief Получение типов столбцов
     * @details Получение типов столбцов по считанным из CSV-файла данным для построения таблицы в базе данных
     * @return Список типов в контейнере QStringList
     */
    QStringList getColumnsType();

    /**
     * @brief Очищает имя базы данных, CSV-файла и таблицы
     */
    void clearNames()
    {
        dbname = "";
        csvname = "";
        tname = "";
    }

    /**
     * @brief Очистка данных модели
     */
    void clearTable();

    /**
     * @brief Перегруженный оператор сравнения моделей на равенство
     */
    const bool operator==(const ConverterModel *model1);

public slots:

    /**
     * @brief Сеттер для имени базы данных
     * @param name - Присваиваемое имя базы данных
     */
    void setDbName(QString name)
    {
        dbname = name;
    }

    /**
     * @brief Сеттер для имени CSV-файла
     * @param name - Присваиваемое имя CSV-файла
     */
    void setCsvName(QString name)
    {
        csvname = name;
    }

    /**
     * @brief Сеттер для имени таблицы
     * @param name - Присваиваемое имя таблицы
     */
    void setTableName(QString name)
    {
        tname = name;
    }

    /**
     * @brief Чтение таблицы из базы данных в модель
     * @return 0 - если чтение прошло успешно, 1 - если произошла ошибка
     */
    bool readFromDbToModel();

    /**
     * @brief Запись данных из модели в CSV-файл
     * @return 0 - если запись прошла успешно, 1 - если произошла ошибка
     */
    bool writeFromModelToCsv();

    /**
     * @brief Чтение данных из CSV-файла в модель
     * @return 0 - если чтение прошло успешно, 1 - если произошла ошибка
     */
    bool readFromCsvToModel();

    /**
     * @brief Запись таблицы из модели в базу данных
     * @return 0 - если запись прошла успешно, 1 - если произошла ошибка
     */
    bool writeFromModelToDb();

    // QAbstractItemModel interface
public:

    /**
     * @brief Возвращает название стоблца модели по номеру
     * @param section - Номер столбца
     * @param orientation - Направление заголовка
     * @param role - Роль элемента
     * @return Название стоблца модели по данному номеру, либо пустую строку, если номер выходит за границы заголовка
     */
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
};

#endif // CONVERTER_H
