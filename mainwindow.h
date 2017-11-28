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
    bool modelIsEmpty;

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

    void readToModel();

    void enableLoadDataButton(bool enable);
    void enableTransformButton(bool enable);

    void transformButtonClicked();

    void clearInput();
    void inputOutputValidator();

    void checkDb();
    void checkCsv();

signals:
    void newCsv(QString);
    void newDb(QString);
    void newTable(QString);

    void transformToDb();
    void transformToCsv();

    void validData(bool);
    void validInput(bool);

    void notNullInput(bool);
    void notNullOutput(bool);

private:
    Ui::MainWindow *ui;
    ConverterModel model;
};

#endif // MAINWINDOW_H
