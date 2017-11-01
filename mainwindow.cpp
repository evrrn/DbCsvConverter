#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_csvdb_button_clicked()
{
    if (!this->convert_flag){
        this->convert_flag = true;
        ui->label->setText(QString("Выберите файл .csv"));
        ui->label_2->setText(QString("Выберите файл базы"));
    }

}

void MainWindow::on_dbcsv_button_clicked()
{
    //this->convert_flag = false;
    if (this->convert_flag){
        this->convert_flag = false;
        ui->label->setText(QString("Выберите файл базы"));
        ui->label_2->setText(QString("Выберите файл .csv"));
    }
}

void MainWindow::on_pushButton_clicked()
{
    if(this->convert_flag){
        QString open_file = QFileDialog::getOpenFileName(0, "Open Dialog", "", "*.csv");
        ui->file_name->setText(open_file);
    //ui->pushButton->setText(QString("nenenene"));
    }
    else{
        QString open_file = QFileDialog::getOpenFileName(0, "Open Dialog", "", "");
        ui->file_name->setText(open_file);
    }
}

void MainWindow::on_pushButton_2_clicked()
{   if(this->convert_flag){
        QString open_file = QFileDialog::getOpenFileName(0, "Open Dialog", "", "");
        ui->label_3->setText(open_file);
    }
    else{
        QString open_file = QFileDialog::getSaveFileName(0, "Open Dialog", "", "");
        ui->label_3->setText(open_file);

    }
}
