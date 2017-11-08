#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QFileInfo>
#include <QVBoxLayout>
#include <QtSql>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->csvtodb_flag = true;
    setVisibleFromTableName(false);
    setVisibleToTableName(false);
    connect(ui->csvdb_button,SIGNAL(clicked()),this,SLOT(csvdb_button_clicked()));
    connect(ui->dbcsv_button,SIGNAL(clicked()),this,SLOT(dbcsv_button_clicked()));
    connect(ui->csvdb_button,SIGNAL(clicked()),this,SLOT(clear_input()));
    connect(ui->dbcsv_button,SIGNAL(clicked()),this,SLOT(clear_input()));
    connect(ui->select_from_file_button,SIGNAL(clicked()),this, SLOT(select_from_file_button_clicked()));
    connect(ui->select_to_file_button,SIGNAL(clicked()),this, SLOT(select_to_file_button_clicked()));
    connect(ui->show_from_table_button,SIGNAL(clicked()),this,SLOT(show_from_table_button_clicked()));
    connect(ui->edit_from_table_name,SIGNAL(editingFinished()),this,SLOT(edit_from_table_name_editingFinished()));
    connect(ui->edit_to_table_name,SIGNAL(editingFinished()),this,SLOT(edit_to_table_name_editingFinished()));
    connect(ui->transform_button,SIGNAL(clicked()),this,SLOT(transform_button_clicked()));

    view_result_table = new QTableView;
    //sdb = QSqlDatabase::addDatabase("QSQLITE");
    //view_result_table->setGeometry(100,100,100,100);
    ui->horizontalLayout_9->addWidget(view_result_table);
            //QPushButton *b = new QPushButton(this);
    //QVBoxLayout *layout = new QVBoxLayout(this);
    //layout->addWidget(b);
    //layout->addWidget(listtable);
    //b->setText(QString("TEST"));
    //ui->gridLayout->addWidget(b);
    //ui->centralWidget->addWidget(&listtable);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setVisibleFromTableName(bool flag){
    ui->select_from_table_lable->setVisible(flag);
    ui->edit_from_table_name->setVisible(flag);
    ui->show_from_table_button->setVisible(flag);
}
void MainWindow::setVisibleToTableName(bool flag){
    ui->select_to_table_lable->setVisible(flag);
    ui->edit_to_table_name->setVisible(flag);
    ui->show_to_table_button->setVisible(flag);
}

void MainWindow::csvdb_button_clicked()
{
    if (!this->csvtodb_flag){
        this->csvtodb_flag = true;
        ui->select_from_file_label->setText(QString("Выберите файл .csv"));
        ui->select_to_file_label->setText(QString("Выберите файл базы"));
        //очистка полей после изменения типа
    }

}

void MainWindow::dbcsv_button_clicked()
{
    //this->convert_flag = false;
    if (this->csvtodb_flag){
        this->csvtodb_flag = false;
        ui->select_from_file_label->setText(QString("Выберите файл базы"));
        ui->select_to_file_label->setText(QString("Выберите файл .csv"));
    }
}

void MainWindow::select_from_file_button_clicked()
{
    if(this->csvtodb_flag){
        csv_file_name = QFileDialog::getOpenFileName(0, "Open Dialog", "", "*.csv");
        ui->file_from_name->setText(QFileInfo(csv_file_name).fileName());
    }
    else{
        db_file_name = QFileDialog::getOpenFileName(0, "Open Dialog", "", "");
        ui->file_from_name->setText( QFileInfo(db_file_name).fileName());
        ui->edit_from_table_name->clear();
        if(db_file_name != ""){
            setVisibleFromTableName(true);
        }
        else{
            setVisibleFromTableName(false);
        }
    }
}

void MainWindow::select_to_file_button_clicked()
{   if(this->csvtodb_flag){
        db_file_name = QFileDialog::getOpenFileName(0, "Open Dialog", "", "");
        ui->file_to_name->setText(QFileInfo(db_file_name).fileName());
        ui->edit_to_table_name->clear();
        if(db_file_name != ""){
            setVisibleToTableName(true);
        }
        else{
            setVisibleToTableName(false);
        }
        /***
        QSqlDatabase sdb = QSqlDatabase::addDatabase("QSQLITE");
        sdb.setDatabaseName(open_file);
        if (!sdb.open())
            qDebug() << sdb.lastError().text();
        this->listtable.addItems(sdb.tables());
        listtable.show();
        */


    }
    else{
        csv_file_name = QFileDialog::getSaveFileName(0, "Open Dialog", "");
        ui->file_to_name->setText(QFileInfo(csv_file_name).fileName());

    }
}

void MainWindow::show_from_table_button_clicked()
{
    //view table
/*
    //QSqlDatabase sdb = QSqlDatabase::addDatabase("QSQLITE");
    this->sdb.setDatabaseName(db_file_name);
    if (!sdb.open())
        qDebug() << sdb.lastError().text();
    this->listtable.addItems(sdb.tables());
    //listtable.show();

    QSqlTableModel *model = new QSqlTableModel(this, sdb);
       model->setTable(table_name);
       //this->view_result_table = new QTableView;
       view_result_table->setModel(model);
       //view->show();
*/
    //Проверить есть ли данное имя в базе
}

void MainWindow::edit_from_table_name_editingFinished()
{
    table_name = ui->edit_from_table_name->text();
}

void MainWindow::edit_to_table_name_editingFinished()
{
    table_name = ui->edit_to_table_name->text();
}
/*
void MainWindow::on_edit_table_name_2_textChanged(const QString &arg1)
{
    table_name = arg1;
}
*/
void MainWindow::clear_input(){
    setVisibleFromTableName(false);
    setVisibleToTableName(false);
    ui->file_from_name->clear();
    ui->file_to_name->clear();
    ui->edit_from_table_name->clear();
    ui->edit_to_table_name->clear();
    this->csv_file_name="";
    this->db_file_name="";
    this->table_name="";
    this->view_result_table->setModel(0);
    this->view_result_table->setHorizontalHeader(0);
    this->view_result_table->setVerticalHeader(0);
}


void MainWindow::transform_button_clicked()
{
    //csvtodb
    if(this->csvtodb_flag){

    }
    //dbtocsv
    else{

    }
}
