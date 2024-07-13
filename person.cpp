#include "person.h"
#include "ui_person.h"

Person::Person(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Person)
{
    ui->setupUi(this);
}

Person::Person(QSqlDatabase *db, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Person),
    db(*db)
{
    ui->setupUi(this);
    this->db.open();
    model = new QSqlTableModel(this, this->db);
    model->setTable("persons");
    model->select();
    ui->person_table_vew->setModel(model);
}


Person::~Person()
{
    delete ui;
    db.close();
}

void Person::on_person_table_vew_clicked(const QModelIndex &index)
{
    row = index.model()->index(index.row(), 0).data().toInt();
}


void Person::on_exit_button_clicked()
{
    this->close();
}


void Person::on_add_button_clicked()
{
    query = new QSqlQuery;
    query->prepare("INSERT INTO persons(first_name, last_name, middle_name, pass_number, pass_batch, city, street, house, flat, inn)"
                   " VALUES(:first_name, :last_name, :middle_name, :pass_number, :pass_batch, :city, :street, :house, :flat, :inn);");
    query->bindValue(":first_name", ui->first_name->text());
    query->bindValue(":last_name", ui->last_name->text());
    query->bindValue(":middle_name", ui->middle_name->text());
    query->bindValue(":pass_number", ui->pass_number->text());
    query->bindValue(":pass_batch", ui->pass_batch->text());
    query->bindValue(":city", ui->city->text());
    query->bindValue(":street", ui->street->text());
    query->bindValue(":house", ui->house->text());
    query->bindValue(":flat", ui->flat->text().toInt());
    query->bindValue(":inn", ui->inn->text());
    query->exec();
    delete query;
    model->select();
}


void Person::on_remove_button_clicked()
{
    query = new QSqlQuery;
    query->prepare("DELETE FROM persons WHERE id = :id;");
    query->bindValue(":id", row);
    query->exec();
    delete query;
    model->select();
}

