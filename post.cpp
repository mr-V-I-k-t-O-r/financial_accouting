#include "post.h"
#include "ui_post.h"

Post::Post(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Post)
{}

Post::Post(QSqlDatabase *db, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Post),
    db(*db)
{
    ui->setupUi(this);
    if(this->db.open())
    {
        model = new QSqlTableModel(this, this->db);
        model->setTable("posts");
        model->select();
        ui->post_table_view->setModel(model);
    }
}

Post::~Post()
{
    db.close();
    delete model;
    delete ui;
}

void Post::on_exit_button_clicked()
{
    this->close();
}


void Post::on_add_button_clicked()
{
    query = new QSqlQuery;
    query->prepare("INSERT INTO posts(name) VALUES(:name);");
    query->bindValue(":name", ui->name->text());
    query->exec();
    delete query;
    model->select();
}


void Post::on_remove_button_clicked()
{
    query = new QSqlQuery;
    query->prepare("DELETE FROM posts WHERE id = :id;");
    query->bindValue(":id", row);
    query->exec();
    delete query;
    model->select();
}


void Post::on_post_table_view_clicked(const QModelIndex &index)
{
    row = index.model()->index(index.row(), 0).data().toInt();
}

