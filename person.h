#ifndef PERSON_H
#define PERSON_H

#include <QDialog>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlTableModel>

namespace Ui {
class Person;
}

class Person : public QDialog
{
    Q_OBJECT

public:
    explicit Person(QWidget *parent = nullptr);
    explicit Person(QSqlDatabase *db, QWidget *parent = nullptr);

    ~Person();

private slots:
    void on_person_table_vew_clicked(const QModelIndex &index);

    void on_exit_button_clicked();

    void on_add_button_clicked();

    void on_remove_button_clicked();

private:
    Ui::Person *ui;
    QSqlDatabase db;
    QSqlTableModel* model;
    int row;
    QSqlQuery* query;
};

#endif // PERSON_H
