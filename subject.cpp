#include "subject.h"
#include "ui_subject.h"

Subject::Subject(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Subject)
{}

Subject::Subject(QSqlDatabase *db, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Subject),
    db(*db)
{
    ui->setupUi(this);
    if(this->db.open())
    {
        model = new QSqlTableModel(this, this->db);
        model->setTable("subjects");
        model->select();
        ui->subject_table_view->setModel(model);
    }
}

Subject::~Subject()
{
    db.close();
    delete ui;
    delete model;
}

void Subject::on_subject_table_view_clicked(const QModelIndex &index)
{
    row = index.model()->index(index.row(), 0).data().toInt();
}


void Subject::on_exit_button_clicked()
{
    this->close();
}


void Subject::on_add_button_clicked()
{
    query = new QSqlQuery;
    query->prepare("INSERT INTO subjects(name) VALUES(:name);");
    query->bindValue(":name", ui->name->text());
    query->exec();
    delete query;
    model->select();
}


void Subject::on_remove_button_clicked()
{
    query = new QSqlQuery;
    query->prepare("DELETE FROM subjects WHERE id = :id;");
    query->bindValue(":id", row);
    query->exec();
    delete query;
    model->select();
}

