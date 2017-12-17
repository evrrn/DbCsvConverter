#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QFileInfo>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tableView->setModel(&model);

    connect(this, SIGNAL(newDb(QString)), &model, SLOT(setDbName(QString)));
    connect(this, SIGNAL(newTable(QString)), &model, SLOT(setTableName(QString)));
    connect(this, SIGNAL(newCsv(QString)), &model, SLOT(setCsvName(QString)));

    connect(this, SIGNAL(notNullInput(bool)), this, SLOT(readToModel(bool)));

    connect(this, SIGNAL(validInput(bool)), this, SLOT(inputOutputValidator()));
    connect(this, SIGNAL(notNullOutput(bool)), this, SLOT(inputOutputValidator()));

    connect(this, SIGNAL(newDb(QString)), this, SLOT(checkDb()));
    connect(this, SIGNAL(newTable(QString)), this, SLOT(checkDb()));
    connect(this, SIGNAL(newCsv(QString)), this, SLOT(checkCsv()));

    connect(this, SIGNAL(validData(bool)), this, SLOT(enableTransformButton(bool)));

    connect(this, SIGNAL(transformToCsv()), &model, SLOT(writeFromModelToCsv()));
    connect(this, SIGNAL(transformToDb()), &model, SLOT(writeFromModelToDb()));

    connect(this, SIGNAL(newLog()), this, SLOT(changeLog()));

    this->csvToDbFlag = true;
    this->modelIsEmpty = true;

    ui->transformButton->setEnabled(false);

    setVisibleFromTableName(false);
    setVisibleToTableName(false);

    connect(ui->csvDbButton, SIGNAL(clicked()), this, SLOT(csvDbButtonClicked()));
    connect(ui->dbCsvButton, SIGNAL(clicked()), this, SLOT(dbCsvButtonClicked()));

    connect(ui->selectFromFileButton, SIGNAL(clicked()), this, SLOT(selectFromFileButtonClicked()));
    connect(ui->selectToFileButton, SIGNAL(clicked()), this, SLOT(selectToFileButtonClicked()));

    connect(ui->chooseFromTableName,SIGNAL(currentIndexChanged(int)),this,SLOT(currentTableNameChanged()));
    connect(ui->editToTableName, SIGNAL(editingFinished()), this, SLOT(editToTableNameEditingFinished()));

    connect(ui->transformButton, SIGNAL(clicked()), this ,SLOT(transformButtonClicked()));

    this->model.output<<"Приложение запущено";
    emit newLog();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setVisibleFromTableName(bool flag)
{
    ui->selectFromTableLable->setVisible(flag);
    ui->chooseFromTableName->setVisible(flag);
}

void MainWindow::setVisibleToTableName(bool flag)
{
    ui->selectToTableLable->setVisible(flag);
    ui->editToTableName->setVisible(flag);
}

void MainWindow::csvDbButtonClicked()
{
    if (!this->csvToDbFlag)
    {
        this->csvToDbFlag = true;
        ui->selectFromFileLabel->setText(QString("Choose file .csv"));
        ui->selectToFileLabel->setText(QString("Choose database"));
        clearInput();
    }
}

void MainWindow::dbCsvButtonClicked()
{
    if (this->csvToDbFlag)
    {
        this->csvToDbFlag = false;
        ui->selectFromFileLabel->setText(QString("Choose database"));
        ui->selectToFileLabel->setText(QString("Choose file .csv"));
        clearInput();
    }
}

void MainWindow::selectFromFileButtonClicked()
{
    if (this->csvToDbFlag)
    {
        csvName = QFileDialog::getOpenFileName(0, "Open Dialog", "", "*.csv");
        ui->fileFromLabel->setText(QFileInfo(csvName).fileName());
        emit newCsv(csvName);
    }

    else
    {
        dbName = QFileDialog::getOpenFileName(0, "Open Dialog", "", "");
        ui->fileFromLabel->setText( QFileInfo(dbName).fileName());
        ui->chooseFromTableName->clear();

        if (dbName != "")
            setVisibleFromTableName(true);
        else
            setVisibleFromTableName(false);

        emit newDb(dbName);

        ui->chooseFromTableName->addItem("");
        ui->chooseFromTableName->addItems(this->model.readListOfTables());
    }
}

void MainWindow::selectToFileButtonClicked()
{
    if (this->csvToDbFlag)
    {
        dbName = QFileDialog::getOpenFileName(0, "Open Dialog", "", "");
        ui->fileToLabel->setText(QFileInfo(dbName).fileName());
        ui->editToTableName->clear();

        if(dbName != "")
            setVisibleToTableName(true);
        else
            setVisibleToTableName(false);

        emit newDb(dbName);
    }

    else
    {
        csvName = QFileDialog::getSaveFileName(0, "Open Dialog", "");
        ui->fileToLabel->setText(QFileInfo(csvName).fileName());
        emit newCsv(csvName);
    }
}

void MainWindow::editToTableNameEditingFinished()
{
    tableName = ui->editToTableName->text();
    emit newTable(tableName);
}

void MainWindow::currentTableNameChanged(){
    tableName = ui->chooseFromTableName->currentText();
    emit newTable(tableName);
}

void MainWindow::clearInput(){
    setVisibleFromTableName(false);
    setVisibleToTableName(false);

    ui->fileFromLabel->clear();
    ui->fileToLabel->clear();
    ui->chooseFromTableName->clear();
    ui->editToTableName->clear();

    this->csvName = "";
    emit newCsv(csvName);
    this->dbName = "";
    emit newDb(dbName);
    this->tableName = "";
    emit newTable(tableName);

    modelIsEmpty = true;
    model.clearTable();
}

void MainWindow::readToModel(bool notNull)
{
    if (notNull)
    {
        if (this->csvToDbFlag)
            model.readFromCsvToModel();
        else
            model.readFromDbToModel();

        modelIsEmpty = false;
        emit validInput(true);
        emit newLog();
    }
}

void MainWindow::transformButtonClicked()
{
    if (this->csvToDbFlag)
        emit transformToDb();
    else
        emit transformToCsv();

    emit newLog();
}

void MainWindow::enableTransformButton(bool enable)
{
    ui->transformButton->setEnabled(enable);
}

void MainWindow::inputOutputValidator()
{
    emit validData(dbName != "" && tableName != "" && csvName != "" && !modelIsEmpty);
}

void MainWindow::checkCsv()
{
    if (this->csvToDbFlag)
    {
        modelIsEmpty = true;
        model.clearTable();
        emit validInput(false);

        emit notNullInput(csvName != "");
    }

    else
        emit notNullOutput(csvName != "");
}

void MainWindow::checkDb()
{
    if (!this->csvToDbFlag)
    {
        modelIsEmpty = true;
        model.clearTable();
        emit validInput(false);

        emit notNullInput(dbName != "" && tableName != "");
    }

    else
        emit notNullOutput(dbName != "" && tableName != "");
}

void MainWindow::changeLog()
{
    ui->logList->clear();
    ui->logList->addItems(model.output);
}
