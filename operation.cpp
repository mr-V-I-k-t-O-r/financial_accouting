#include "operation.h"
#include "ui_operation.h"
#include <QSqlError>
#include <unistd.h>

Operation::Operation(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Operation)
{}

Operation::Operation(QSqlDatabase *db, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Operation),
    db(*db)
{
    ui->setupUi(this);
    this->db.open();
    model = new QSqlTableModel(this, this->db);
    model->setTable("operations");
    model->select();
    ui->operation_table_view->setModel(model);

    accounts = new QSqlQueryModel(this);
    accounts->setQuery("SELECT name FROM accounts;");
    ui->account->setModel(accounts);

    subjects = new QSqlQueryModel(this);
    subjects->setQuery("SELECT name FROM subjects;");
    ui->subject->setModel(subjects);

    employees = new QSqlQueryModel(this);
    employees->setQuery("SELECT concat(last_name, ' ', first_name, ' ', middle_name) FROM employees;");
    ui->employee->setModel(employees);

    types = new QSqlQueryModel(this);
    types->setQuery("SELECT name FROM operation_types;");
    ui->type->setModel(types);

    persons = new QSqlQueryModel(this);
    persons->setQuery("SELECT concat(last_name, ' ', first_name, ' ', middle_name) FROM persons;");
    ui->person->setModel(persons);

    organizations = new QSqlQueryModel(this);
    organizations->setQuery("SELECT name FROM organizations;");
    ui->organization->setModel(organizations);
}

Operation::~Operation()
{
    db.close();
    delete ui;
    delete model;
    delete accounts;
    delete subjects;
    delete employees;
    delete types;
    delete persons;
    delete organizations;
}

void Operation::on_operation_table_view_clicked(const QModelIndex &index)
{
    row = index.model()->index(index.row(), 0).data().toInt();
}


void Operation::on_exit_button_clicked()
{
    this->close();
}


void Operation::on_add_button_clicked()
{
    query = new QSqlQuery;
    if(organization == 0 && person != 0){
        query->prepare("INSERT INTO operations(summ, date, account_id, subject_id, employee_id, operation_type, person_id) "
                       "VALUES(:summ, :date, :account_id, :subject_id, :employee_id, :operation_type, :person_id);");
        query->bindValue(":person_id", person);
    }
    else if(person == 0 && organization != 0){
        query->prepare("INSERT INTO operations(summ, date, account_id, subject_id, employee_id, operation_type, organization_id) "
                       "VALUES(:summ, :date, :account_id, :subject_id, :employee_id, :operation_type, :organization_id);");
        query->bindValue(":organization_id", organization);
    }
    else{
        ui->error->setText("выберите организацию или физ.лицо");
        return;
    }
    query->bindValue(":summ", ui->summ->text());
    query->bindValue(":date", ui->date->date());
    query->bindValue(":account_id", account);
    query->bindValue(":subject_id", subject);
    query->bindValue(":employee_id", employee);
    query->bindValue(":operation_type", type);
    query->exec();
    delete query;
    model->select();
    query = new QSqlQuery;
    if(income)
        query->prepare("UPDATE accounts SET summ = summ + :summ where id = :account;");
    else
        query->prepare("UPDATE accounts SET summ = summ - :summ where id = :account;");
    query->bindValue(":summ", ui->summ->text());
    query->bindValue(":account", account);
    query->exec();
    delete query;
}


void Operation::on_remove_button_clicked()
{
    query = new QSqlQuery;
    query->prepare("SELECT operation_types.income, accounts.id, operations.summ FROM operations"
                   " JOIN operation_types ON (operation_types.id = operations.operation_type)"
                   " JOIN accounts ON (accounts.id = operations.account_id) WHERE operations.id = :id;");
    query->bindValue(":id", row);
    query->exec();
    while(query->next()){
        income = query->value(0).toBool();
        account = query->value(1).toInt();
        summ = query->value(2).toInt();
    }
    delete query;

    query = new QSqlQuery;
    if(income){
        query->prepare("UPDATE accounts SET summ = summ - :summ where id = :account;");
    }
    else{
        query->prepare("UPDATE accounts SET summ = summ + :summ where id = :account;");
    }
    query->bindValue(":summ", summ);
    query->bindValue(":account", account);
    query->exec();
    delete query;

    query = new QSqlQuery;
    query->prepare("DELETE FROM operations WHERE id = :id;");
    query->bindValue(":id", row);
    query->exec();
    delete query;
    model->select();

}


void Operation::on_account_clicked(const QModelIndex &index)
{
    query = new QSqlQuery;
    query->prepare("SELECT id FROM accounts WHERE name = :name;");
    query->bindValue(":name", index.data().toString());
    query->exec();
    while(query->next()){
        account = query->value(0).toInt();
    }
    delete query;
}


void Operation::on_subject_clicked(const QModelIndex &index)
{
    query = new QSqlQuery;
    query->prepare("SELECT id FROM subjects WHERE name = :name;");
    query->bindValue(":name", index.data().toString());
    query->exec();
    while(query->next()){
        subject = query->value(0).toInt();
    }
    delete query;
}


void Operation::on_employee_clicked(const QModelIndex &index)
{
    query = new QSqlQuery;
    query->prepare("SELECT id FROM employees WHERE concat(last_name, ' ', first_name, ' ', middle_name) = :value;");
    query->bindValue(":value", index.data().toString());
    query->exec();
    while(query->next()){
        employee = query->value(0).toInt();
    }
    delete query;
}


void Operation::on_type_clicked(const QModelIndex &index)
{
    query = new QSqlQuery;
    query->prepare("SELECT id, income FROM operation_types WHERE name = :name;");
    query->bindValue(":name", index.data().toString());
    query->exec();
    while(query->next()){
        type = query->value(0).toInt();
        income = query->value(1).toBool();
    }
    delete query;
}


void Operation::on_person_clicked(const QModelIndex &index)
{
    query = new QSqlQuery;
    query->prepare("SELECT id FROM persons WHERE concat(last_name, ' ', first_name, ' ', middle_name) = :value;");
    query->bindValue(":value", index.data().toString());
    query->exec();
    while(query->next()){
        person = query->value(0).toInt();
        organization = 0;
    }
    delete query;
}


void Operation::on_organization_clicked(const QModelIndex &index)
{
    query = new QSqlQuery;
    query->prepare("SELECT id FROM organizations WHERE name = :name;");
    query->bindValue(":name", index.data().toString());
    query->exec();
    while(query->next()){
        organization = query->value(0).toInt();
        person = 0;
    }
    delete query;
}

