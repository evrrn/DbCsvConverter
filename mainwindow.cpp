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

    connect(this, SIGNAL(notNullInput(bool)), this, SLOT(enableLoadDataButton(bool)));

    connect(this, SIGNAL(validInput(bool)), this, SLOT(inputOutputValidator()));
    connect(this, SIGNAL(notNullOutput(bool)), this, SLOT(inputOutputValidator()));

    connect(this, SIGNAL(newDb(QString)), this, SLOT(checkDb()));
    connect(this, SIGNAL(newTable(QString)), this, SLOT(checkDb()));
    connect(this, SIGNAL(newCsv(QString)), this, SLOT(checkCsv()));

    connect(this, SIGNAL(validData(bool)), this, SLOT(enableTransformButton(bool)));

    connect(ui->loadDataButton, SIGNAL(clicked(bool)), this, SLOT(readToModel()));
    connect(this, SIGNAL(transformToCsv()), &model, SLOT(writeFromModelToCsv()));

    this->csvToDbFlag = true;
    this->modelIsEmpty = true;

    ui->transformButton->setEnabled(false);
    ui->loadDataButton->setEnabled(false);

    setVisibleFromTableName(false);
    setVisibleToTableName(false);

    connect(ui->csvDbButton, SIGNAL(clicked()), this, SLOT(csvDbButtonClicked()));
    connect(ui->dbCsvButton, SIGNAL(clicked()), this, SLOT(dbCsvButtonClicked()));

    connect(ui->selectFromFileButton, SIGNAL(clicked()), this, SLOT(selectFromFileButtonClicked()));
    connect(ui->selectToFileButton, SIGNAL(clicked()), this, SLOT(selectToFileButtonClicked()));

    connect(ui->editFromTableName, SIGNAL(editingFinished()), this, SLOT(editFromTableNameEditingFinished()));
    connect(ui->editToTableName, SIGNAL(editingFinished()), this, SLOT(editToTableNameEditingFinished()));
    connect(ui->transformButton, SIGNAL(clicked()), this ,SLOT(transformButtonClicked()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setVisibleFromTableName(bool flag)
{
    ui->selectFromTableLable->setVisible(flag);
    ui->editFromTableName->setVisible(flag);
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
        ui->editFromTableName->clear();

        if (dbName != "")
            setVisibleFromTableName(true);
        else
            setVisibleFromTableName(false);

        emit newDb(dbName);
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

void MainWindow::editFromTableNameEditingFinished()
{
    tableName = ui->editFromTableName->text();
    emit newTable(tableName);
}

void MainWindow::editToTableNameEditingFinished()
{
    tableName = ui->editToTableName->text();
    emit newTable(tableName);
}

void MainWindow::clearInput(){
    setVisibleFromTableName(false);
    setVisibleToTableName(false);

    ui->fileFromLabel->clear();
    ui->fileToLabel->clear();
    ui->editFromTableName->clear();
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

void MainWindow::readToModel()
{
    if (!this->csvToDbFlag)
        model.readFromDbToModel();
    //else
        //model.readFromCsvToModel();

    modelIsEmpty = false;
    emit validInput(true);
}

void MainWindow::transformButtonClicked()
{
    if (this->csvToDbFlag)
        emit transformToDb();
    else
        emit transformToCsv();
}

void MainWindow::enableTransformButton(bool enable)
{
    ui->transformButton->setEnabled(enable);
}

void MainWindow::enableLoadDataButton(bool enable)
{
    ui->loadDataButton->setEnabled(enable);
}

void MainWindow::inputOutputValidator()
{
    emit validData(dbName != "" && tableName != "" && csvName != "" && !modelIsEmpty);
}

void MainWindow::checkCsv()
{
    if (this->csvToDbFlag)
    {
        emit notNullInput(csvName != "");

        modelIsEmpty = true;
        model.clearTable();
        emit validInput(false);
    }
    else
        emit notNullOutput(csvName != "");;
}

void MainWindow::checkDb()
{
    if (!this->csvToDbFlag)
    {
        emit notNullInput(dbName != "" && tableName != "");

        modelIsEmpty = true;
        model.clearTable();
        emit validInput(false);
    }
    else
        emit notNullOutput(dbName != "" && tableName != "");
}

