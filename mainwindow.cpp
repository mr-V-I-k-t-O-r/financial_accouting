#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "account.h"
#include "employee.h"
#include "post.h"
#include "operation.h"
#include "subject.h"
#include "create_report.h"
#include "type.h"
#include "organization.h"
#include "person.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    db = QSqlDatabase::addDatabase("QPSQL");
    db.setHostName("localhost");
    db.setPort(5432);
    db.setDatabaseName("");
    db.setUserName("");
    db.setPassword("");
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_account_clicked()
{
    Account window(&db);
    window.setModal(true);
    window.exec();
}


void MainWindow::on_employee_clicked()
{
    Employee window(&db);
    window.setModal(true);
    window.exec();
}


void MainWindow::on_post_clicked()
{
    Post window(&db);
    window.setModal(true);
    window.exec();
}


void MainWindow::on_operation_clicked()
{
    Operation window(&db);
    window.setModal(true);
    window.exec();
}


void MainWindow::on_subject_clicked()
{
    Subject window(&db);
    window.setModal(true);
    window.exec();
}


void MainWindow::on_create_report_clicked()
{
    Create_Report window(&db);
    window.setModal(true);
    window.exec();
}


void MainWindow::on_type_clicked()
{
    Type window(&db);
    window.setModal(true);
    window.exec();
}


void MainWindow::on_organization_clicked()
{
    Organization window(&db);
    window.setModal(true);
    window.exec();
}


void MainWindow::on_person_clicked()
{
    Person window(&db);
    window.setModal(true);
    window.exec();
}

