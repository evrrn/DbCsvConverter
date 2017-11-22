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

    connect(this, SIGNAL(namesArentEmpty(bool)), this, SLOT(enable_transform_button(bool)));


    connect(ui->show_from_table_button, SIGNAL(clicked(bool)), &model, SLOT(readFromDbToModel()));
    connect(ui->show_to_table_button, SIGNAL(clicked(bool)), &model, SLOT(readFromCsvToModel()));

    connect(this, SIGNAL(transformToCsv()), &model, SLOT(writeFromModelToCsv()));
    connect(this, SIGNAL(transformToDb()), &model, SLOT(writeFromModelToDb()));

    // обратно connect(ui->show_to_table_button, SIGNAL(clicked(bool)), &model, SLOT(readFromCsvToModel()));
    //connect(this, SIGNAL(csvToDb()), &model, SLOT(writeFromModelToDb()));

    this->csvtodb_flag = true;

    ui->transform_button->setEnabled(false);
    setVisibleFromTableName(false);
    setVisibleToTableName(false);

    connect(ui->csvdb_button, SIGNAL(clicked()), this, SLOT(csvdb_button_clicked()));
    connect(ui->dbcsv_button, SIGNAL(clicked()), this, SLOT(dbcsv_button_clicked()));

    connect(ui->select_from_file_button, SIGNAL(clicked()), this, SLOT(select_from_file_button_clicked()));
    connect(ui->select_to_file_button, SIGNAL(clicked()), this, SLOT(select_to_file_button_clicked()));

    connect(ui->edit_from_table_name, SIGNAL(editingFinished()), this, SLOT(edit_from_table_name_editingFinished()));
    connect(ui->edit_to_table_name, SIGNAL(editingFinished()), this, SLOT(edit_to_table_name_editingFinished()));
    connect(ui->transform_button, SIGNAL(clicked()), this ,SLOT(transform_button_clicked()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setVisibleFromTableName(bool flag)
{
    ui->select_from_table_lable->setVisible(flag);
    ui->edit_from_table_name->setVisible(flag);
    ui->show_from_table_button->setVisible(flag);
}

void MainWindow::setVisibleToTableName(bool flag)
{
    ui->select_to_table_lable->setVisible(flag);
    ui->edit_to_table_name->setVisible(flag);
    ui->show_to_table_button->setVisible(flag);
}

void MainWindow::csvdb_button_clicked()
{
    if (!this->csvtodb_flag)
    {
        this->csvtodb_flag = true;
        ui->select_from_file_label->setText(QString("Выберите файл .csv"));
        ui->select_to_file_label->setText(QString("Выберите файл базы"));
        clear_input();
    }
}

void MainWindow::dbcsv_button_clicked()
{
    if (this->csvtodb_flag)
    {
        this->csvtodb_flag = false;
        ui->select_from_file_label->setText(QString("Выберите файл базы"));
        ui->select_to_file_label->setText(QString("Выберите файл .csv"));
        clear_input();
    }
}

void MainWindow::select_from_file_button_clicked()
{
    if (this->csvtodb_flag)
    {
        csv_file_name = QFileDialog::getOpenFileName(0, "Open Dialog", "", "*.csv");
        ui->file_from_label->setText(QFileInfo(csv_file_name).fileName());
        emit newCsv(csv_file_name);
    }
    else
    {
        db_file_name = QFileDialog::getOpenFileName(0, "Open Dialog", "", "");
        ui->file_from_label->setText( QFileInfo(db_file_name).fileName());
        ui->edit_from_table_name->clear();

        if (db_file_name != "")
            setVisibleFromTableName(true);
        else
            setVisibleFromTableName(false);

        emit newDb(db_file_name);
    }
}

void MainWindow::select_to_file_button_clicked()
{
    if (this->csvtodb_flag)
    {
        db_file_name = QFileDialog::getOpenFileName(0, "Open Dialog", "", "");
        ui->file_to_label->setText(QFileInfo(db_file_name).fileName());
        ui->edit_to_table_name->clear();

        if(db_file_name != "")
            setVisibleToTableName(true);
        else
            setVisibleToTableName(false);

        emit newDb(db_file_name);
    }
    else
    {
        csv_file_name = QFileDialog::getSaveFileName(0, "Open Dialog", "");
        ui->file_to_label->setText(QFileInfo(csv_file_name).fileName());
        emit newCsv(csv_file_name);
    }
}

void MainWindow::edit_from_table_name_editingFinished()
{
    table_name = ui->edit_from_table_name->text();
    emit newTable(table_name);
}

void MainWindow::edit_to_table_name_editingFinished()
{
    table_name = ui->edit_to_table_name->text();
    emit newTable(table_name);
}

void MainWindow::clear_input(){
    setVisibleFromTableName(false);
    setVisibleToTableName(false);

    ui->file_from_label->clear();
    ui->file_to_label->clear();
    ui->edit_from_table_name->clear();
    ui->edit_to_table_name->clear();

    this->csv_file_name = "";
    emit newCsv(csv_file_name);
    this->db_file_name = "";
    emit newDb(db_file_name);
    this->table_name = "";
    emit newTable(table_name);

    model.clearTable();
}


void MainWindow::transform_button_clicked()
{
    if (this->csvtodb_flag)
        emit transformToDb();
    else
        emit transformToCsv();
}

void MainWindow::enable_transform_button(bool enable)
{
    ui->transform_button->setEnabled(enable);
}

void MainWindow::names_arent_empty()
{
    if (csv_file_name != "" && db_file_name != "" && table_name != "") {
        emit namesArentEmpty(true);
        return;
    }
    emit namesArentEmpty(false);
}
