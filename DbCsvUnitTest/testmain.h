#include <QString>
#include <QDir>
#include <QtTest>
#include <QtTest/QtTest>
#include <QCryptographicHash>
#include "../converter.h"

class DbCsvUnitTest : public QObject
{
    Q_OBJECT

public:
    ConverterModel testModel;
    ConverterModel originalModel;

    QString inputCsv = "../DbCsvUnitTest/input/CsvTest.csv";
    QString inputDb = "../DbCsvUnitTest/input/DbTest";
    QString tableName = "TableTest";

    QString outputCsv = "../DbCsvUnitTest/output/CsvTest.csv";
    QString outputDb = "../DbCsvUnitTest/output/DbTest";

    QString benchmarkCsv = "../DbCsvUnitTest/benchmark/CsvTest.csv";
    QString benchmarkDb = "../DbCsvUnitTest/benchmark/DbTest";

public:
    DbCsvUnitTest();
    ~DbCsvUnitTest();

    void fillModel(ConverterModel* model);
    void dropTable(QString dbname, QString tname);
    void clearModels();

    bool dbComparison(QString db1, QString db2);
    bool fileComparison(QString file1, QString file2);

private Q_SLOTS:
    void cleanup();

    void readFromDbToModel();
    void writeFromModelToCsv();
    void dbToCsv();
    void dbToCsvAndBack();

    void readFromCsvToModel();
    void writeFromModelToDb();
    void csvToDb();
    void csvToDbAndBack();
};
