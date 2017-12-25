#include "testmain.h"

DbCsvUnitTest::DbCsvUnitTest()
{
}

DbCsvUnitTest::~DbCsvUnitTest()
{
}

void DbCsvUnitTest::cleanup()
{
    clearModels();
}

bool DbCsvUnitTest::dbComparison(QString db1, QString db2)
{
    if (!QFile::exists(db1))
       return false;

    if (!QFile::exists(db2))
       return false;

    QSqlDatabase::removeDatabase("fstConnection");
    QSqlDatabase sdb1 = QSqlDatabase::addDatabase("QSQLITE", "fstConnection");
    sdb1.setDatabaseName(db1);
    if (!sdb1.open())
        return false;

    QSqlDatabase::removeDatabase("sndConnection");
    QSqlDatabase sdb2 = QSqlDatabase::addDatabase("QSQLITE","sndConnection");
    sdb2.setDatabaseName(db2);
    if (!sdb2.open())
        return false;

    QStringList tables_1 = sdb1.tables();
    QStringList tables_2 = sdb2.tables();
    if (tables_1 != tables_2)
       return false;

    for (int i = 0; i < tables_1.size(); i++)
    {
        QSqlRecord columns1 = sdb1.record(tables_1[i]);
        QSqlRecord columns2 = sdb2.record(tables_2[i]);
        if  (columns1 != columns2)
            return false;

        for (int j = 0; j < columns1.count(); j++)
        {
            if (columns1.field(j) != columns2.field(j))
                return false;
        }

        QList<QStringList> rows1, rows2;

        QSqlQuery query1("SELECT * FROM " + tables_1[i], sdb1);
        while (query1.next())
        {
            rows1 << QStringList();
            for(int j = 0; j < columns1.count(); j++)
                 rows1.last() << query1.value(j).toString();
        }

        QSqlQuery query2("SELECT * FROM " + tables_2[i], sdb2);
        while (query2.next())
        {
            rows2 << QStringList();
            for(int j = 0; j < columns2.count(); j++)
                 rows2.last() << query2.value(j).toString();
        }

        if (rows1 != rows2)
            return false;
    }

    return true;
}

bool DbCsvUnitTest::fileComparison(QString f1, QString f2)
{
    QCryptographicHash hash1(QCryptographicHash::Sha1);
    QCryptographicHash hash2(QCryptographicHash::Sha1);

    QFile file1(f1);
    QFile file2(f2);

    if (file1.open(QIODevice::ReadOnly))
        hash1.addData(file1.readAll());
    else
        return 0;

    if (file2.open( QIODevice::ReadOnly))
        hash2.addData(file2.readAll());
    else
        return 0;

    QByteArray sig1 = hash1.result();
    QByteArray sig2 = hash2.result();

    return (sig1 == sig2);
}

void DbCsvUnitTest::fillModel(ConverterModel* model)
{
    model->header<<"IntCol"<<"RealCol"<<"TextCol";
    model->rows<<(QStringList()<<"1"<<"4"<<"IN,SH;as\\HmvV");
    model->rows<<(QStringList()<<"2"<<"7"<<"XstKj/vhvod");
    model->rows<<(QStringList()<<"3"<<"3,5"<<"Qk kX|uNVaH");
    model->rows<<(QStringList()<<"4"<<"5"<<"OuTXo^EW»SxJ");
    model->rows<<(QStringList()<<"5"<<"7,3"<<"VShM copp");
}

void DbCsvUnitTest::dropTable(QString dbname, QString tname)
{
    QSqlDatabase::removeDatabase("dropTable");
    QSqlDatabase sdb = QSqlDatabase::addDatabase("QSQLITE","dropTable");
    sdb.setDatabaseName(dbname);
    if (!sdb.open())
        return;

    QSqlQuery *querydrop = new QSqlQuery("DROP TABLE " + tname, sdb);
    querydrop->exec();
}

void DbCsvUnitTest::clearModels()
{
    testModel.clearTable();
    testModel.clearNames();

    originalModel.clearTable();
    originalModel.clearNames();
}

QTEST_APPLESS_MAIN(DbCsvUnitTest)
