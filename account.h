#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <QDialog>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlTableModel>

namespace Ui {
class Account;
}

class Account : public QDialog
{
    Q_OBJECT

public:
    explicit Account(QWidget *parent = nullptr);
    explicit Account(QSqlDatabase *db, QWidget *parent = nullptr);
    ~Account();

private slots:
    void on_exit_button_clicked();

    void on_add_button_clicked();

    void on_remove_button_clicked();

    void on_account_table_view_clicked(const QModelIndex &index);

private:
    Ui::Account *ui;
    QSqlDatabase db;
    QSqlTableModel* model;
    int row;
    QSqlQuery* query;
};

#endif // ACCOUNT_H
