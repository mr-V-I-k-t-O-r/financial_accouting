#ifndef TYPE_H
#define TYPE_H

#include <QDialog>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlTableModel>

namespace Ui {
class Type;
}

class Type : public QDialog
{
    Q_OBJECT

public:
    explicit Type(QWidget *parent = nullptr);
    explicit Type(QSqlDatabase *db, QWidget *parent = nullptr);

    ~Type();

private slots:
    void on_exit_button_clicked();

    void on_add_button_clicked();

    void on_remove_button_clicked();

    void on_type_table_view_clicked(const QModelIndex &index);

    void on_income_clicked();

    void on_expense_clicked();

private:
    Ui::Type *ui;
    QSqlDatabase db;
    QSqlTableModel* model;
    int row;
    QSqlQuery* query;
    bool income;
};

#endif // TYPE_H
