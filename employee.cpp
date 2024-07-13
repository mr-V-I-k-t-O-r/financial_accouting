#include "employee.h"
#include "ui_employee.h"
#include <QSqlError>

Employee::Employee(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Employee)
{}

Employee::Employee(QSqlDatabase *db, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Employee),
    db(*db)
{
    ui->setupUi(this);
    this->db.open();
    model = new QSqlTableModel(this, this->db);
    model->setTable("employees");
    model->select();
    ui->employee_table_view->setModel(model);

    posts = new QSqlQueryModel(this);
    posts->setQuery("SELECT name FROM posts;");
    ui->listView->setModel(posts);
}

Employee::~Employee()
{
    db.close();
    delete ui;
    delete model;

}

void Employee::on_add_button_clicked()
{
    query = new QSqlQuery;
    query->prepare("INSERT INTO employees(first_name, last_name, middle_name, pass_batch, pass_number, city, street, house, flat, inn, post) "
                  "VALUES(:first_name, :last_name, :middle_name, :pass_batch, :pass_number, :city, :street, :house, :flat, :inn, :post);");
    query->bindValue(":first_name", ui->first_name->text());
    query->bindValue(":last_name", ui->last_name->text());
    query->bindValue(":middle_name", ui->middle_name->text());
    query->bindValue(":pass_batch", ui->pass_batch->text().toInt());
    query->bindValue(":pass_number", ui->pass_number->text().toInt());
    query->bindValue(":city", ui->city->text());
    query->bindValue(":street", ui->street->text());
    query->bindValue(":house", ui->house->text());
    query->bindValue(":flat", ui->flat->text().toInt());
    query->bindValue(":inn", ui->inn->text());
    query->bindValue(":post", post);
    query->exec();
    delete query;
    model->select();
}


void Employee::on_remove_button_clicked()
{
    query = new QSqlQuery;
    query->prepare("DELETE FROM employees WHERE id = :id;");
    query->bindValue(":id", row);
    query->exec();
    delete query;
    model->select();
}


void Employee::on_exit_button_clicked()
{
    this->close();
}


void Employee::on_employee_table_view_clicked(const QModelIndex &index)
{
    row = index.model()->index(index.row(), 0).data().toInt();
}



void Employee::on_listView_clicked(const QModelIndex &index)
{
    query = new QSqlQuery;
    query->prepare("SELECT id FROM posts WHERE name = :name;");
    query->bindValue(":name", index.data().toString());
    query->exec();
    while(query->next()){
        post = query->value(0).toInt();
    }
    delete query;
}

