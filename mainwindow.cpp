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
    ui->tableView->setModel(&model);

    ui->select_table_lable_1->setVisible(false);
    ui->edit_table_name_1->setVisible(false);
    ui->show_table_button_1->setVisible(false);
    ui->select_table_lable_2->setVisible(false);
    ui->edit_table_name_2->setVisible(false);
    ui->show_table_button_2->setVisible(false);

    connect(ui->dbcsv_button, SIGNAL(clicked(bool)), &model, SLOT(readFromDbToModel()));

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

void MainWindow::on_csvdb_button_clicked()
{
    if (!this->csvtodb_flag){
        this->csvtodb_flag = true;
        ui->select_file_label_1->setText(QString("Выберите файл .csv"));
        ui->select_file_label_2->setText(QString("Выберите файл базы"));
        //очистка полей после изменения типа
    }

}

void MainWindow::on_dbcsv_button_clicked()
{
    //emit valueChanged();
    //this->convert_flag = false;
    if (this->csvtodb_flag){
        this->csvtodb_flag = false;
        ui->select_file_label_1->setText(QString("Выберите файл базы"));
        ui->select_file_label_2->setText(QString("Выберите файл .csv"));
    }
}

void MainWindow::on_select_file_button_1_clicked()
{
    if(this->csvtodb_flag){
        csv_file_name = QFileDialog::getOpenFileName(0, "Open Dialog", "", "*.csv");
        ui->file_name_1->setText(QFileInfo(csv_file_name).fileName());
    }
    else{
        db_file_name = QFileDialog::getOpenFileName(0, "Open Dialog", "", "");
        ui->file_name_1->setText( QFileInfo(db_file_name).fileName());
        if(db_file_name != ""){
            ui->select_table_lable_2->setVisible(true);
            ui->edit_table_name_2->setVisible(true);
            ui->show_table_button_2->setVisible(true);
        }
        else{
            ui->select_table_lable_2->setVisible(false);
            ui->edit_table_name_2->setVisible(false);
            ui->show_table_button_2->setVisible(false);
        }
        /***open db. new substr
        QSqlDatabase sdb = QSqlDatabase::addDatabase("QSQLITE");
        sdb.setDatabaseName(open_file);
        if (!sdb.open())
            qDebug() << sdb.lastError().text();
        this->listtable.ad
        ***/
    }
}

void MainWindow::on_select_file_button_2_clicked()
{   if(this->csvtodb_flag){
        db_file_name = QFileDialog::getOpenFileName(0, "Open Dialog", "", "");
        ui->file_name_2->setText(QFileInfo(db_file_name).fileName());
        if(db_file_name != ""){
            ui->select_table_lable_1->setVisible(true);
            ui->edit_table_name_1->setVisible(true);
            ui->show_table_button_1->setVisible(true);
        }
        else{
            ui->select_table_lable_1->setVisible(false);
            ui->edit_table_name_1->setVisible(false);
            ui->show_table_button_1->setVisible(false);
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
        ui->file_name_2->setText(QFileInfo(csv_file_name).fileName());

    }
}

void MainWindow::on_show_table_button_2_clicked()
{
    //view table
    /*
    QSqlDatabase sdb = QSqlDatabase::addDatabase("QSQLITE");
    sdb.setDatabaseName(db_file_name);
    if (!sdb.open())
        qDebug() << sdb.lastError().text();
    this->listtable.addItems(sdb.tables());
    //listtable.show();

    QSqlTableModel *model = new QSqlTableModel(this, sdb);
       model->setTable(table_name);
       QTableView *view = new QTableView;
       view->setModel(model);
       view->show();
    */
    //Проверить есть ли данное имя в базе
}

void MainWindow::on_edit_table_name_2_editingFinished()
{
    table_name = ui->edit_table_name_2->text();
}

void MainWindow::on_edit_table_name_1_editingFinished()
{
    table_name = ui->edit_table_name_1->text();
}

void MainWindow::on_edit_table_name_2_textChanged(const QString &arg1)
{
    table_name = arg1;
}

/*void MainWindow::on_pushButton_3_clicked()
{

}*/

void MainWindow::on_transform_button_clicked()
{
    //csvtodb
    if(this->csvtodb_flag){

    }
    //dbtocsv
    else{

    }
}
