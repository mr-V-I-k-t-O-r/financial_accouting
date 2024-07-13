#ifndef SUBJECT_H
#define SUBJECT_H

#include <QDialog>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlTableModel>

namespace Ui {
class Subject;
}

class Subject : public QDialog
{
    Q_OBJECT

public:
    explicit Subject(QWidget *parent = nullptr);
    explicit Subject(QSqlDatabase *db, QWidget *parent = nullptr);

    ~Subject();

private slots:
    void on_subject_table_view_clicked(const QModelIndex &index);

    void on_exit_button_clicked();

    void on_add_button_clicked();

    void on_remove_button_clicked();

private:
    Ui::Subject *ui;
    QSqlDatabase db;
    QSqlTableModel* model;
    int row;
    QSqlQuery* query;
};

#endif // SUBJECT_H
