#ifndef CREATE_REPORT_H
#define CREATE_REPORT_H

#include <QDialog>
#include <QtSql/QSqlDatabase>
#include <QSqlQuery>

namespace Ui {
class Create_Report;
}

class Create_Report : public QDialog
{
    Q_OBJECT

public:
    explicit Create_Report(QWidget *parent = nullptr);
    explicit Create_Report(QSqlDatabase *db, QWidget *parent = nullptr);

    ~Create_Report();

private slots:
    void on_exit_button_clicked();

    void on_report_button_clicked();

private:
    Ui::Create_Report *ui;
    QSqlDatabase db;
    QSqlQuery *query;
    int summ_income = 0;
    int summ_expense = 0;
    int summ_total = 0;
    int count_income = 0;
    int count_expense = 0;
    int count_total = 0;
    int summ;
    bool income;
};

#endif // CREATE_REPORT_H
