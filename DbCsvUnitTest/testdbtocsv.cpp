#include "testmain.h"

void DbCsvUnitTest::readFromDbToModel()
{
    testModel.setDbName(inputDb);
    testModel.setTableName(tableName);
    testModel.readFromDbToModel();

    originalModel.setTableName(tableName);
    fillModel(&originalModel);

    QVERIFY(testModel.operator==(&originalModel));
}

void DbCsvUnitTest::writeFromModelToCsv()
{
    fillModel(&testModel);

    testModel.setCsvName(outputCsv);
    testModel.writeFromModelToCsv();

    bool result = fileComparison(outputCsv, benchmarkCsv);
    QFile::remove(outputCsv);

    QVERIFY(result);
}

void DbCsvUnitTest::dbToCsv()
{
    testModel.setDbName(inputDb);
    testModel.setTableName(tableName);
    testModel.readFromDbToModel();

    testModel.setCsvName(outputCsv);
    testModel.writeFromModelToCsv();

    bool result = fileComparison(outputCsv, benchmarkCsv);
    QFile::remove(outputCsv);

    QVERIFY(result);
}

void DbCsvUnitTest::dbToCsvAndBack()
{
    testModel.setDbName(inputDb);
    testModel.setTableName(tableName);
    testModel.setCsvName(outputCsv);

    testModel.readFromDbToModel();
    testModel.writeFromModelToCsv();

    testModel.setDbName(outputDb);

    testModel.readFromCsvToModel();
    testModel.writeFromModelToDb();

    bool result = dbComparison(outputDb, benchmarkDb);
    dropTable(outputDb, tableName);

    QVERIFY(result);
}
