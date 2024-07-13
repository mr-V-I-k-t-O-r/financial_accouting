#include "account.h"
#include "ui_account.h"

#include <QSqlError>

Account::Account(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Account)
{
    ui->setupUi(this);
}

Account::Account(QSqlDatabase *db, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Account),
    db(*db)
{
    ui->setupUi(this);
    if(this->db.open())
    {
        model = new QSqlTableModel(this, this->db);
        model->setTable("accounts");
        model->select();
        ui->account_table_view->setModel(model);
    }
}


Account::~Account()
{
    db.close();
    delete ui;
    delete model;
}

void Account::on_exit_button_clicked()
{
    this->close();
}


void Account::on_add_button_clicked()
{
    query = new QSqlQuery;
    query->prepare("INSERT INTO accounts (name, summ) VALUES (:name, :summ);");
    query->bindValue(":name", ui->name->text());
    query->bindValue(":summ", ui->summ->text().toInt());
    query->exec();
    delete query;
    model->select();
}


void Account::on_remove_button_clicked()
{
    query = new QSqlQuery;
    query->prepare("DELETE FROM accounts WHERE id = :id;");
    query->bindValue(":id", row);
    query->exec();
    delete query;
    model->select();
}


void Account::on_account_table_view_clicked(const QModelIndex &index)
{
    row = index.model()->index(index.row(), 0).data().toInt();
}

