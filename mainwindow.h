#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "converter.h"
#include <QMainWindow>
#include <QPushButton>
#include <QFileDialog>
#include <QString>
#include <QLabel>
#include <QComboBox>
#include <QStatusBar>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    /**
     * @brief Конструктор главного окна программы
     * @param parent - Виджет родитель
     */
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    /**
     * @brief csvToDbFlag - Флаг, определяющий вид преобразования
     */
    bool csvToDbFlag;
    /**
     * @brief modelIsEmpty
     */
    bool modelIsEmpty;
    /**
     * @brief csvName - Имя CSV-файла
     */
    QString csvName;
    /**
     * @brief dbName - Имя базы данных
     */
    QString dbName;
    /**
     * @brief tableName - Имя таблицы
     */
    QString tableName;

    void setVisibleFromTableName(bool flag);
    void setVisibleToTableName(bool flag);

private slots:
    void csvDbButtonClicked();
    void dbCsvButtonClicked();

    void selectFromFileButtonClicked();
    void selectToFileButtonClicked();

    void editToTableNameEditingFinished();
    void currentTableNameChanged();

    void readToModel(bool notNull);

    void enableTransformButton(bool enable);
    void transformButtonClicked();

    void clearInput();

    void inputOutputValidator();

    void checkDb();
    void checkCsv();

    void changeLog();

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

    void newLog();

private:
    Ui::MainWindow *ui;
    ConverterModel model;

    void readListOfTables();
};


#endif // MAINWINDOW_H
