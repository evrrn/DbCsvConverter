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

    connect(this, SIGNAL(newDb(QString)), this, SLOT(names_arent_empty()));
    connect(this, SIGNAL(newTable(QString)), this, SLOT(names_arent_empty()));
    connect(this, SIGNAL(newCsv(QString)), this, SLOT(names_arent_empty()));

    connect(this, SIGNAL(namesArentEmpty(bool)), this, SLOT(enableTransformButton(bool)));


    connect(ui->showFromTableButton, SIGNAL(clicked(bool)), &model, SLOT(readFromDbToModel()));
    connect(this, SIGNAL(transformToCsv()), &model, SLOT(writeFromModelToCsv()));

    // обратно connect(ui->show_to_table_button, SIGNAL(clicked(bool)), &model, SLOT(readFromCsvToModel()));
    //connect(this, SIGNAL(csvToDb()), &model, SLOT(writeFromModelToDb()));

    this->csvToDbFlag = true;

    ui->transformButton->setEnabled(false);
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
    ui->showFromTableButton->setVisible(flag);
}

void MainWindow::setVisibleToTableName(bool flag)
{
    ui->selectToTableLable->setVisible(flag);
    ui->editToTableName->setVisible(flag);
    ui->showToTableButton->setVisible(flag);
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

    model.clearTable();
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

void MainWindow::names_arent_empty()
{
    if (csvName != "" && dbName != "" && tableName != "")
    {
        emit namesArentEmpty(true);
        return;
    }
    emit namesArentEmpty(false);
}
