#include <QString>
#include <QtTest>

class DbCsvUnitTest : public QObject
{
    Q_OBJECT

public:
    DbCsvUnitTest();

private Q_SLOTS:
    void testCase1_data();
    void testCase1();
};

DbCsvUnitTest::DbCsvUnitTest()
{
}

void DbCsvUnitTest::testCase1_data()
{
    QTest::addColumn<QString>("data");
    QTest::newRow("0") << QString();
}

void DbCsvUnitTest::testCase1()
{
    QFETCH(QString, data);
    QVERIFY2(true, "Failure");
}

QTEST_APPLESS_MAIN(DbCsvUnitTest)

#include "tst_dbcsv.moc"
