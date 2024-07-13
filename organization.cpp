#include "organization.h"
#include "ui_organization.h"

Organization::Organization(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Organization)
{
    ui->setupUi(this);
}

Organization::Organization(QSqlDatabase *db, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Organization),
    db(*db)
{
    ui->setupUi(this);
    this->db.open();
    model = new QSqlTableModel(this, this->db);
    model->setTable("organizations");
    model->select();
    ui->organization_table_view->setModel(model);
}

Organization::~Organization()
{
    delete ui;
    delete model;
    db.close();
}

void Organization::on_organization_table_view_clicked(const QModelIndex &index)
{
    row = index.model()->index(index.row(), 0).data().toInt();
}


void Organization::on_exit_button_clicked()
{
    this->close();
}


void Organization::on_add_button_clicked()
{
    query = new QSqlQuery;
    query->prepare("INSERT INTO organizations(name, city, street, house, flat, inn, account_number)"
                   " VALUES(:name, :city, :street, :house, :flat, :inn, :account_number);");
    query->bindValue(":name", ui->name->text());
    query->bindValue(":city", ui->city->text());
    query->bindValue(":street", ui->street->text());
    query->bindValue(":house", ui->house->text());
    query->bindValue(":flat", ui->flat->text());
    query->bindValue(":inn", ui->inn->text());
    query->bindValue(":account_number", ui->account_number->text());
    query->exec();
    delete query;
    model->select();
}


void Organization::on_remove_button_clicked()
{
    query = new QSqlQuery;
    query->prepare("DELETE FROM organizations WHERE id = :id;");
    query->bindValue(":id", row);
    query->exec();
    delete query;
    model->select();
}

