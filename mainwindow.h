#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "converter.h"
#include <QMainWindow>
#include <QPushButton>
#include <QFileDialog>
#include <QString>
#include <QLabel>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    bool csvtodb_flag;

    QString csv_file_name;
    QString db_file_name;
    QString table_name;

    void setVisibleFromTableName(bool flag);
    void setVisibleToTableName(bool flag);

private slots:
    void csvdb_button_clicked();
    void dbcsv_button_clicked();

    void select_from_file_button_clicked();
    void select_to_file_button_clicked();

    void edit_from_table_name_editingFinished();
    void edit_to_table_name_editingFinished();

    void transform_button_clicked();
    void clear_input();

    void names_arent_empty();
    void enable_transform_button(bool enable);

signals:
    void newCsv(QString);
    void newDb(QString);
    void newTable(QString);

    void transformToDb();
    void transformToCsv();

    void namesArentEmpty(bool);

private:
    Ui::MainWindow *ui;
    ConverterModel model;
};

#endif // MAINWINDOW_H
