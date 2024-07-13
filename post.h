#ifndef POST_H
#define POST_H

#include <QDialog>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlTableModel>

namespace Ui {
class Post;
}

class Post : public QDialog
{
    Q_OBJECT

public:
    explicit Post(QWidget *parent = nullptr);
    explicit Post(QSqlDatabase *db, QWidget *parent = nullptr);

    ~Post();

private slots:
    void on_exit_button_clicked();

    void on_add_button_clicked();

    void on_remove_button_clicked();

    void on_post_table_view_clicked(const QModelIndex &index);

private:
    Ui::Post *ui;
    QSqlDatabase db;
    QSqlTableModel* model;
    int row;
    QSqlQuery* query;
};

#endif // POST_H
