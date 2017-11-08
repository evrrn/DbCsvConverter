#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "converter.h"
#include <QMainWindow>
#include <QPushButton>
#include <QFileDialog>
#include <QString>
#include <QLabel>
#include <QListWidget>
#include <QSqlTableModel>
#include <QTableView>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    bool csvtodb_flag = true;
    QListWidget listtable;
    //true = csv -> db
    //false = db -> csv
    //QSqlTableModel  *model;
    //DataBase        *db;
    //Временные имена, которые будут храниться в модели
    QString csv_file_name;
    QString db_file_name;
    QString table_name;

private slots:
    void on_csvdb_button_clicked();

    void on_dbcsv_button_clicked();

    //void on_pushButton_clicked();

    //void on_pushButton_2_clicked();
    void on_select_file_button_1_clicked();

    void on_select_file_button_2_clicked();

    void on_show_table_button_2_clicked();

    void on_edit_table_name_2_editingFinished();

    void on_edit_table_name_1_editingFinished();

    void on_edit_table_name_2_textChanged(const QString &arg1);

    void on_pushButton_3_clicked();

    void on_transform_button_clicked();

signals:
    //void choose_item_from_list();

private:
    Ui::MainWindow *ui;
    ConverterModel model;
};

#endif // MAINWINDOW_H
