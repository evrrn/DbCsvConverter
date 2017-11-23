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

    bool csvToDbFlag;

    QString csvName;
    QString dbName;
    QString tableName;

    void setVisibleFromTableName(bool flag);
    void setVisibleToTableName(bool flag);

private slots:
    void csvDbButtonClicked();
    void dbCsvButtonClicked();

    void selectFromFileButtonClicked();
    void selectToFileButtonClicked();

    void editFromTableNameEditingFinished();
    void editToTableNameEditingFinished();

    void transformButtonClicked();
    void clearInput();

    void names_arent_empty();
    void enableTransformButton(bool enable);

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
