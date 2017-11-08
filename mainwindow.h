#ifndef MAINWINDOW_H
#define MAINWINDOW_H

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
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    bool csvtodb_flag;
    QListWidget listtable;
    //true = csv -> db
    //false = db -> csv
    //QSqlTableModel  *model;
    //DataBase        *db;
    //Временные имена, которые будут храниться в модели
    QString csv_file_name;
    QString db_file_name;
    QString table_name;
    QTableView *view_result_table;
    //QSqlDatabase sdb;
    void setVisibleFromTableName(bool flag);
    void setVisibleToTableName(bool flag);
    bool condition_checker();
private slots:
    void csvdb_button_clicked();
    void dbcsv_button_clicked();

    void select_from_file_button_clicked();
    void select_to_file_button_clicked();

    void show_from_table_button_clicked();

    void edit_from_table_name_editingFinished();

    void edit_to_table_name_editingFinished();

    //void on_edit_table_name_2_textChanged(const QString &arg1);

    void transform_button_clicked();
    void clear_input();
signals:
    //void choose_item_from_list();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H

/*
1.+ Сделать явные connect
2.+ Переименовать кнопки выбора файла  from, to
3.+ Переставить местами поля ввода для имени таблицы(в начале идет 2, а потом 1, ето не круто)
4. условие для активации кнопки "Преобразовать" и "Вывод таблицы"
5.+ окно для вывода результирующей модели
5.1. size of block
6.+ clear-function
6.1. clear model
*/
