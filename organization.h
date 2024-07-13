#ifndef ORGANIZATION_H
#define ORGANIZATION_H

#include <QDialog>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlTableModel>

namespace Ui {
class Organization;
}

class Organization : public QDialog
{
    Q_OBJECT

public:
    explicit Organization(QWidget *parent = nullptr);
    explicit Organization(QSqlDatabase *db, QWidget *parent = nullptr);

    ~Organization();

private slots:
    void on_organization_table_view_clicked(const QModelIndex &index);

    void on_exit_button_clicked();

    void on_add_button_clicked();

    void on_remove_button_clicked();

private:
    Ui::Organization *ui;
    QSqlDatabase db;
    QSqlTableModel* model;
    int row;
    QSqlQuery* query;
};

#endif // ORGANIZATION_H
