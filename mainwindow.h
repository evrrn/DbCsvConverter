#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QFileDialog>
#include <QString>
#include <QLabel>
#include <QListWidget>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    bool convert_flag = true;
    QListWidget listtable;
    //true = csv -> db
    //false = db -> csv

private slots:
    void on_csvdb_button_clicked();

    void on_dbcsv_button_clicked();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();
signals:
    //void choose_item_from_list();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
