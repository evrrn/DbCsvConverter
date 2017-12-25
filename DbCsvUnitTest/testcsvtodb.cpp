#include "testmain.h"

void DbCsvUnitTest::readFromCsvToModel()
{
    testModel.setCsvName(inputCsv);
    testModel.readFromCsvToModel();

    fillModel(&originalModel);

    QVERIFY(testModel.operator==(&originalModel));
}

void DbCsvUnitTest::writeFromModelToDb()
{
    fillModel(&testModel);

    testModel.setDbName(outputDb);
    testModel.setTableName(tableName);
    testModel.writeFromModelToDb();

    bool result = dbComparison(outputDb, benchmarkDb);
    dropTable(outputDb, tableName);

    QVERIFY(result);
}

void DbCsvUnitTest::csvToDb()
{
    testModel.setCsvName(inputCsv);
    testModel.readFromCsvToModel();

    testModel.setDbName(outputDb);
    testModel.setTableName(tableName);
    testModel.writeFromModelToDb();

    bool result = dbComparison(outputDb, benchmarkDb);
    dropTable(outputDb, tableName);

    QVERIFY(result);
}

void DbCsvUnitTest::csvToDbAndBack()
{
    testModel.setCsvName(inputCsv);
    testModel.setDbName(outputDb);
    testModel.setTableName(tableName);

    testModel.readFromCsvToModel();
    testModel.writeFromModelToDb();

    testModel.setCsvName(outputCsv);

    testModel.readFromDbToModel();
    testModel.writeFromModelToCsv();

    bool result = fileComparison(inputCsv, outputCsv);

    QFile::remove(outputCsv);
    dropTable(outputDb, tableName);

    QVERIFY(result);
}
