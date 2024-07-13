#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include <QDialog>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlTableModel>
#include <QSqlQueryModel>

namespace Ui {
class Employee;
}

class Employee : public QDialog
{
    Q_OBJECT

public:
    explicit Employee(QWidget *parent = nullptr);
    explicit Employee(QSqlDatabase *db, QWidget *parent = nullptr);

    ~Employee();

private slots:
    void on_add_button_clicked();

    void on_remove_button_clicked();

    void on_exit_button_clicked();

    void on_employee_table_view_clicked(const QModelIndex &index);

    void on_listView_clicked(const QModelIndex &index);

private:
    Ui::Employee *ui;
    QSqlDatabase db;
    QSqlQuery* query;
    QSqlTableModel* model;
    int row;
    int post;
    QSqlQueryModel *posts;
};

#endif // EMPLOYEE_H
