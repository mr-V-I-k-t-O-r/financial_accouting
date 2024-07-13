#ifndef OPERATION_H
#define OPERATION_H

#include <QDialog>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlTableModel>

namespace Ui {
class Operation;
}

class Operation : public QDialog
{
    Q_OBJECT

public:
    explicit Operation(QWidget *parent = nullptr);
    explicit Operation(QSqlDatabase *db, QWidget *parent = nullptr);

    ~Operation();

private slots:
    void on_operation_table_view_clicked(const QModelIndex &index);

    void on_exit_button_clicked();

    void on_add_button_clicked();

    void on_remove_button_clicked();

    void on_account_clicked(const QModelIndex &index);

    void on_subject_clicked(const QModelIndex &index);

    void on_employee_clicked(const QModelIndex &index);

    void on_type_clicked(const QModelIndex &index);

    void on_person_clicked(const QModelIndex &index);

    void on_organization_clicked(const QModelIndex &index);

private:
    Ui::Operation *ui;
    QSqlDatabase db;
    QSqlTableModel* model;
    int row;
    int summ;
    QSqlQuery* query;
    int account;
    int subject;
    int employee;
    int type;
    int person = 0;
    int organization = 0;
    QSqlQueryModel *accounts;
    QSqlQueryModel *subjects;
    QSqlQueryModel *employees;
    QSqlQueryModel *types;
    QSqlQueryModel *persons;
    QSqlQueryModel *organizations;
    bool income;

};

#endif // OPERATION_H
