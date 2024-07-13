#include "type.h"
#include "ui_type.h"

Type::Type(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Type)
{
    ui->setupUi(this);
}

Type::Type(QSqlDatabase *db, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Type),
    db(*db)
{
    ui->setupUi(this);
    this->db.open();
    model = new QSqlTableModel(this, this->db);
    model->setTable("operation_types");
    model->select();
    ui->type_table_view->setModel(model);
}

Type::~Type()
{
    delete ui;
    delete model;
    db.close();
}

void Type::on_exit_button_clicked()
{
    this->close();
}


void Type::on_add_button_clicked()
{
    query = new QSqlQuery;
    query->prepare("INSERT INTO operation_types(name, income) VALUES(:name, :income);");
    query->bindValue(":name", ui->name->text());
    query->bindValue(":income", income);
    query->exec();
    delete query;
    model->select();
}


void Type::on_remove_button_clicked()
{
    query = new QSqlQuery;
    query->prepare("DELETE FROM operation_types WHERE id = :id;");
    query->bindValue(":id", row);
    query->exec();
    delete query;
    model->select();
}


void Type::on_type_table_view_clicked(const QModelIndex &index)
{
    row = index.model()->index(index.row(), 0).data().toInt();
    model->select();
}


void Type::on_income_clicked()
{
    income = 1;
}


void Type::on_expense_clicked()
{
    income = 0;
}

